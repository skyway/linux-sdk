//
//  example_room.cpp
//  skyway
//
//  Created by ogura on 2024/12/13.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#include "example_room.hpp"

#include <iostream>

ExampleRoom::ExampleRoom()
    : p2proom_(nullptr),
      room_member_(nullptr),
      renderer_(nullptr),
      capturer_(nullptr),
      threads_(std::vector<std::unique_ptr<std::thread>>()),
      is_leaving_(false) {}

// SkyWayの利用を開始します。
bool ExampleRoom::Setup(const std::string& app_id, const std::string& secret_key) {
    skyway::Context::SkyWayOptions context_options{};

    // SkyWayのログレベルの設定が行えます。
    context_options.log_level = skyway::global::interface::Logger::kWarn;

    // SkyWayのAppIdとSecretKeyを使用して、SkyWayContextをセットアップします。
    // 本番環境ではContext::Setupを使用してください。
    if (!skyway::Context::SetupForDev(app_id, secret_key, nullptr, context_options)) {
        std::cerr << "- [Error] setup failed." << std::endl;
        return false;
    }
    return true;
}

// P2PRoomを検索/作成し、入室します。
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

    // P2PRoomにメンバーを入室させます。
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

// VideoをPublishします。
void ExampleRoom::Publish() {
    // OpenCVを利用した映像をPublishします。
    capturer_         = std::make_shared<skyway::media::opencv::OpenCVCapturerVideoSource>();
    auto video_stream = skyway::media::StreamFactory::CreateVideoStream(capturer_);
    auto video_thread = std::make_unique<std::thread>([this] {
        int count = 0;
        while (!is_leaving_) {
            // 640x480の画面に現在のカウンターを表示します。
            cv::Mat result = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
            cv::putText(result,
                        std::to_string(count),
                        cv::Point(20, 240),
                        cv::FONT_HERSHEY_SIMPLEX,
                        1,
                        cv::Scalar(0xff, 0xff, 0xff),
                        3);
            if (capturer_) {
                capturer_->Render(result);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            count++;
        }
    });
    threads_.emplace_back(std::move(video_thread));

    skyway::room::interface::LocalRoomMember::PublicationOptions publication_options {};
    auto publication = room_member_->Publish(video_stream, publication_options);
    if (publication) {
        std::cout << "- VideoStream Published" << std::endl;
        std::cout << "  - Publication Id: " << publication->Id() << std::endl;
    }
}

// 指定のPublicationをSubscribeします。
bool ExampleRoom::Subscribe(std::shared_ptr<skyway::room::interface::RoomPublication> publication) {
    if (publication->ContentType() == skyway::model::ContentType::kVideo) {
        if (room_member_->Id() == publication->Publisher()->Id()) {
            // 自身がPublishしたPublicationはSubscribeできないので無視します。
            return false;
        }
        if (this->IsSubscribed(publication)) {
            // 既にSubscribeしている場合は無視します。
            return false;
        }

        if (renderer_) {
            // 既に映像を出力している場合はSubscribeしません。
            std::cout << "- VideoStream Subscribe Canceled" << std::endl;
            std::cout << "  - Already set renderer" << std::endl;
            return false;
        }

        skyway::room::interface::LocalRoomMember::SubscriptionOptions subscription_options {};
        auto subscription = room_member_->Subscribe(publication->Id(), subscription_options);
        if (!subscription) {
            return false;
        }
        auto stream = std::dynamic_pointer_cast<skyway::core::stream::remote::RemoteVideoStream>(
            subscription->Stream());
        // OpenCVを利用して映像を表示するようにします。
        auto renderer = std::make_unique<skyway::media::opencv::OpenCVVideoRenderer>();
        renderer->RegisterListener(this);
        renderer->Render(stream);
        renderer_ = std::move(renderer);

        std::cout << "- VideoStream Subscribed" << std::endl;
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
    std::cout << "- [Event] StreamPublished: Id " << publication->Id() << std::endl;

    // イベントリスナーからSkyWayの操作を行う場合は別スレッドで実行する必要があります。
    auto subscribe_thread = std::make_unique<std::thread>(
        [this, threads_publication = std::move(publication)]() mutable {
            this->Subscribe(std::move(threads_publication));
        });
    threads_.emplace_back(std::move(subscribe_thread));
}

// Impl skyway::media::opencv::OpenCVVideoRenderer::Listener
void ExampleRoom::OnFrame(cv::Mat mat) {
    // 受信した映像をそのまま表示します。
    cv::imshow("OpenCVVideoRenderer", mat);
    cv::waitKey(1);
}

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
