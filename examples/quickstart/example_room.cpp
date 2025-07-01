//
//  example_room.cpp
//  skyway
//
//  Created by ogura on 2024/2/2.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#include "example_room.hpp"

#include <iostream>

ExampleRoom::ExampleRoom(const std::string& renderer_device_name, bool is_notify)
    : p2proom_(nullptr),
      room_member_(nullptr),
      renderer_(nullptr),
      data_stream_(nullptr),
      renderer_device_name_(renderer_device_name),
      threads_(std::vector<std::unique_ptr<std::thread>>()),
      is_leaving_(false),
      is_notify_(is_notify) {}

// SkyWayの利用を開始します。
bool ExampleRoom::Setup(const std::string& token) {
    skyway::Context::SkyWayOptions context_options{};

    // SkyWayのログレベルの設定が行えます。
    // context_options.log_level = skyway::global::interface::Logger::kInfo;

    if (!skyway::Context::Setup(token, nullptr, context_options)) {
        std::cerr << "- [Error] setup failed." << std::endl;
        return false;
    }
    return true;
}

// P2PRoomを検索/作成し、Joinします。
bool ExampleRoom::JoinRoom(const std::string& room_name) {
    // P2PRoomを検索/作成します。
    skyway::room::interface::RoomInitOptions room_init;
    room_init.name = room_name;
    p2proom_       = skyway::room::p2p::P2PRoom::FindOrCreate(room_init);
    if (!p2proom_) {
        std::cerr << "- [Error] room failed." << std::endl;
        return false;
    }
    // P2PRoomにイベントリスナ(skyway::room::interface::Room::EventListenerの実装)を登録します。
    p2proom_->AddEventListener(this);

    // P2PRoomの情報を出力します。
    std::cout << "# Room" << std::endl;
    if (p2proom_->Name()) {
        std::cout << "- Name: " << p2proom_->Name().value() << std::endl;
    }
    std::cout << "- Id: " << p2proom_->Id() << std::endl;

    // P2PRoomに既にいるメンバーの一覧を表示します。
    std::cout << "- Room Members" << std::endl;
    for (auto& members : p2proom_->Members()) {
        std::cout << "  - Id: " << members->Id() << std::endl;
    }

    // P2PRoomにメンバーをJoinさせます。
    skyway::room::interface::RoomMemberInitOptions room_options;
    room_member_ = p2proom_->Join(room_options);
    if (!room_member_) {
        std::cerr << "- [Error] p2proom join failed." << std::endl;
        return false;
    }
    std::cout << "- LocalRoomMember Joined" << std::endl;
    std::cout << "  - Id: " << room_member_->Id() << std::endl;

    return true;
}

// Video/Audio/DataをPublishします。
void ExampleRoom::Publish() {
    // ビデオデバイスを列挙し、任意のデバイスをpublishします。
    auto video_devices = skyway::media::DeviceManager::GetVideoDevices();
    if (video_devices.size() > 0) {
        std::cout << "- VideoDevices" << std::endl;
        for (auto device : video_devices) {
            std::cout << "  - Index: " << device.index << " Name: " << device.name << std::endl;
        }

        // デバイスのindex番号を入力します。
        int device_index;
        std::cout << "- Enter the index of the video device to be published: ";
        std::cin >> device_index;
        if (device_index >= 0 && device_index < video_devices.size()) {
            auto video_stream =
                skyway::media::StreamFactory::CreateVideoStream(video_devices[device_index]);
            skyway::room::interface::LocalRoomMember::PublicationOptions publication_options {};
            auto publication = room_member_->Publish(video_stream, publication_options);
            if (publication) {
                std::cout << "  - VideoStream Published" << std::endl;
                std::cout << "    - Publication Id: " << publication->Id() << std::endl;
            }
        } else {
            std::cout << "  - Out of range" << std::endl;
        }
    }

    // デフォルトで設定されている音声入力デバイスをPublishします。
    auto audio_devices = skyway::media::DeviceManager::GetRecordDevices();
    if (audio_devices.size() > 0) {
        auto device = audio_devices[0];
        skyway::media::DeviceManager::SetRecordingDevice(device);
        auto audio_stream = skyway::media::StreamFactory::CreateAudioStream();
        skyway::room::interface::LocalRoomMember::PublicationOptions publication_options {};
        auto publication = room_member_->Publish(audio_stream, publication_options);
        if (publication) {
            std::cout << "- AudioStream Published" << std::endl;
            std::cout << "  - Device Index: " << device.index << std::endl;
            std::cout << "  - Device Name: " << device.name << std::endl;
            std::cout << "  - Publication Id: " << publication->Id() << std::endl;
        }
    }

    // DataStreamをPublishします。
    data_stream_ = skyway::media::StreamFactory::CreateDataStream();

    // 一定間隔でメッセージを送信するthreadを作成し、threads_に追加します。
    auto data_thread = std::make_unique<std::thread>([this] {
        auto count = 0;
        while (!is_leaving_) {
            auto data = "send msg: " + std::to_string(count);
            data_stream_->Write(data);
            if (is_notify_) {
                std::cout << "<!-- [Event] DataStream Message Send: " << data << " -->"
                          << std::endl;
            }
            count++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    threads_.emplace_back(std::move(data_thread));

    skyway::room::interface::LocalRoomMember::PublicationOptions publication_options {};
    auto publication = room_member_->Publish(data_stream_, publication_options);
    if (publication) {
        std::cout << "- DataStream Published" << std::endl;
        std::cout << "  - Publication Id: " << publication->Id() << std::endl;
    }
}

// 指定のpublicationをsubscribeします。
bool ExampleRoom::Subscribe(std::shared_ptr<skyway::room::interface::RoomPublication> publication) {
    if (room_member_->Id() == publication->Publisher()->Id()) {
        // 自身がPublishしたPublicationはSubscribeできないので無視します。
        return false;
    }
    if (this->IsSubscribed(publication)) {
        // 既にSubscribeしている場合は無視します。
        return false;
    }

    // PublicationのContentTypeに応じてメディアを出力します。
    skyway::room::interface::LocalRoomMember::SubscriptionOptions subscription_options {};
    if (publication->ContentType() == skyway::model::ContentType::kVideo) {
        if (renderer_device_name_ == "") {
            // 出力先を指定していない場合はSubscribeしません。
            std::cout << "- VideoStream Subscribe Canceled" << std::endl;
            std::cout << "  - Video device not specified" << std::endl;
            return false;
        }
        if (renderer_) {
            // 既に映像を出力している場合はSubscribeしません。
            std::cout << "- VideoStream Subscribe Canceled" << std::endl;
            std::cout << "  - Already set renderer" << std::endl;
            return false;
        }
        auto subscription = room_member_->Subscribe(publication->Id(), subscription_options);
        if (!subscription) {
            return false;
        }
        auto stream = std::dynamic_pointer_cast<skyway::core::stream::remote::RemoteVideoStream>(
            subscription->Stream());

        // 映像を出力デバイスに書き込みます。
        skyway::media::V4l2VideoRendererOptions monitor_opt;
        monitor_opt.scaled_width  = 1920;
        monitor_opt.scaled_height = 1080;
        renderer_ =
            std::make_unique<skyway::media::V4l2VideoRenderer>(renderer_device_name_, monitor_opt);
        renderer_->Render(stream);

        std::cout << "- VideoStream Subscribed" << std::endl;
        std::cout << "  - Device : " << renderer_device_name_ << std::endl;
        std::cout << "  - Specified Width: " << monitor_opt.scaled_width << std::endl;
        std::cout << "  - Specified Height: " << monitor_opt.scaled_height << std::endl;
        std::cout << "  - Publication Id: " << publication->Id() << std::endl;
        std::cout << "  - Subscription Id: " << subscription->Id() << std::endl;
    } else if (publication->ContentType() == skyway::model::ContentType::kAudio) {
        auto devices = skyway::media::DeviceManager::GetPlayoutDevices();
        if (devices.size() > 0) {
            auto device = devices[0];
            skyway::media::DeviceManager::SetPlayoutDevice(device);
            // 音声はSubscribeと同時に再生されます。
            auto subscription = room_member_->Subscribe(publication->Id(), subscription_options);
            if (!subscription) {
                return false;
            }
            std::cout << "- AudioStream Subscribed" << std::endl;
            std::cout << "  - Name: " << device.name << std::endl;
            std::cout << "  - Publication Id: " << publication->Id() << std::endl;
            std::cout << "  - Subscription Id: " << subscription->Id() << std::endl;
        }
    } else if (publication->ContentType() == skyway::model::ContentType::kData) {
        auto subscription = room_member_->Subscribe(publication->Id(), subscription_options);
        if (!subscription) {
            return false;
        }
        auto data_stream =
            std::dynamic_pointer_cast<skyway::core::stream::remote::RemoteDataStream>(
                subscription->Stream());
        // P2PRoomにイベントリスナ(skyway::core::stream::remote::RemoteDataStream::Listenerの実装)を登録します。
        data_stream->AddListener(this);
        std::cout << "- DataStream Subscribed" << std::endl;
        std::cout << "  - Publication Id: " << publication->Id() << std::endl;
        std::cout << "  - Subscription Id: " << subscription->Id() << std::endl;
    }
    return true;
}

// P2PRoomに存在するPublication全てに対してSubscribeを試みます。
void ExampleRoom::SubscribeAll() {
    for (auto& publication : p2proom_->Publications()) {
        this->Subscribe(publication);
    }
}

// P2PRoomから退出します。
bool ExampleRoom::LeaveRoom() {
    if (!room_member_) {
        return false;
    }
    is_leaving_ = true;
    // P2PRoomに紐づくイベントリスナの登録を解除します。
    if (p2proom_) {
        p2proom_->RemoveEventListener(this);
    }
    // 各threadの終了を待ちます。
    for (auto& th : threads_) {
        if (th && th->joinable()) {
            th->join();
        }
    }
    is_leaving_ = false;
    return room_member_->Leave();
}

// SkyWayの利用を終了します。
void ExampleRoom::Dispose() { skyway::Context::Dispose(); }

// Impl skyway::room::interface::Room::EventListener
void ExampleRoom::OnStreamPublished(
    std::shared_ptr<skyway::room::interface::RoomPublication> publication) {
    if (is_notify_) {
        std::cout << "<!-- [Event] StreamPublished: Id " << publication->Id() << "-->" << std::endl;
    }

    // イベントリスナーからSkyWayの操作を行う場合は別スレッドで実行する必要があります。
    auto subscribe_thread = std::make_unique<std::thread>(
        [this, threads_publication = std::move(publication)]() mutable {
            this->Subscribe(std::move(threads_publication));
        });
    threads_.emplace_back(std::move(subscribe_thread));
}

// Impl skyway::core::stream::remote::RemoteDataStream::Listener
void ExampleRoom::OnData(const std::string& data) {
    if (is_notify_) {
        std::cout << "<!-- [Event] DataStream Message Received: " << data << "-->" << std::endl;
    }
}
void ExampleRoom::OnDataBuffer(const uint8_t* data, size_t length) {
    if (is_notify_) {
        std::cout << "<!-- [Event] DataStream BinaryData Received: Length=" << length << "-->"
                  << std::endl;
    }
};

// 指定のPublicationをSubscribeしているかチェックします。
bool ExampleRoom::IsSubscribed(
    std::shared_ptr<skyway::room::interface::RoomPublication> publication) {
    auto subscriptions = publication->Subscriptions();
    auto find =
        std::find_if(subscriptions.begin(),
                     subscriptions.end(),
                     [&](std::shared_ptr<skyway::room::interface::RoomSubscription>& subscription) {
                         return subscription->Subscriber()->Id() == room_member_->Id();
                     });
    return find != subscriptions.end();
}
