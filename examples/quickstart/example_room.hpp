//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_EXAMPLES_QUICKSTART_EXAMPLE_ROOM_HPP_
#define SKYWAY_EXAMPLES_QUICKSTART_EXAMPLE_ROOM_HPP_

#include <skyway/context.hpp>
#include <skyway/media/device_manager.hpp>
#include <skyway/media/stream/interface/local/local_data_stream.hpp>
#include <skyway/media/stream/interface/remote/remote_data_stream.hpp>
#include <skyway/media/stream/interface/remote/remote_video_stream.hpp>
#include <skyway/media/stream_factory.hpp>
#include <skyway/media/v4l2_video_renderer.hpp>
#include <skyway/room/room.hpp>

// Roomの操作を行うクラスです。
class ExampleRoom : public skyway::room::interface::Room::EventListener,
                    public skyway::media::stream::interface::remote::RemoteDataStream::Listener {
public:
    ExampleRoom(const std::string& renderer_device_name);

    // SkyWayの利用を開始します。
    bool Setup(const std::string& app_id, const std::string& secret_key);

    // Roomを検索/作成し、入室します。
    bool JoinRoom(const std::string& room_name);

    // Video/Audio/DataをPublishします。
    void Publish();

    // 指定のPublicationをSubscribeします。
    bool Subscribe(std::shared_ptr<skyway::room::interface::RoomPublication> publication);

    // Roomに存在するPublication全てに対してSubscribeを試みます。
    void SubscribeAll();

    // Roomから退出します。
    bool LeaveRoom();

    // SkyWayの利用を終了します。
    void Dispose();

    // Impl skyway::room::interface::Room::EventListener
    void OnStreamPublished(
        std::shared_ptr<skyway::room::interface::RoomPublication> publication) override;

    // Impl skyway::media::stream::interface::remote::RemoteDataStream::Listener
    void OnData(const std::string& data) override;
    void OnDataBuffer(const uint8_t* data, size_t length) override;

private:
    // 指定のPublicationをSubscribeしているかチェックします。
    bool IsSubscribed(std::shared_ptr<skyway::room::interface::RoomPublication> publication);

    std::shared_ptr<skyway::room::Room> room_;
    std::shared_ptr<skyway::room::LocalRoomMember> room_member_;
    std::unique_ptr<skyway::media::V4l2VideoRenderer> renderer_;
    std::shared_ptr<skyway::media::stream::interface::local::LocalDataStream> data_stream_;
    std::string renderer_device_name_;
    std::vector<std::unique_ptr<std::thread>> threads_;
    std::atomic<bool> is_leaving_;
};

#endif  // SKYWAY_EXAMPLES_QUICKSTART_EXAMPLE_ROOM_HPP_
