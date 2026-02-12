//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_EXAMPLES_SFU_EXAMPLE_ROOM_HPP_
#define SKYWAY_EXAMPLES_SFU_EXAMPLE_ROOM_HPP_

#include <skyway/context.hpp>
#include <skyway/media/device_manager.hpp>
#include <skyway/media/stream_factory.hpp>
#include <skyway/media/v4l2_video_renderer.hpp>
#include <skyway/room/sfu/sfu_room.hpp>

// Roomの操作を行うクラスです。
class ExampleRoom : public skyway::room::interface::Room::EventListener {
public:
    ExampleRoom(const std::string& renderer_device_name);

    // SkyWayの利用を開始します。
    bool Setup(const std::string& app_id, const std::string& secret_key);

    // SFURoomを検索/作成し、入室します。
    bool JoinRoom(const std::string& room_name);

    // Video/AudioをPublishします。
    void Publish();

    // 指定のPublicationをSubscribeします。
    bool Subscribe(std::shared_ptr<skyway::room::interface::RoomPublication> publication);

    // SFURoomに存在するPublication全てに対してSubscribeを試みます。
    void SubscribeAll();

    // SFURoomから退出します。
    bool LeaveRoom();

    // SkyWayの利用を終了します。
    void Dispose();

    // Impl skyway::room::interface::Room::EventListener
    void OnStreamPublished(
        std::shared_ptr<skyway::room::interface::RoomPublication> publication) override;

private:
    // 指定のPublicationをSubscribeしているかチェックします。
    bool IsSubscribed(std::shared_ptr<skyway::room::interface::RoomPublication> publication);

    std::shared_ptr<skyway::room::sfu::SFURoom> sfu_room_;
    std::shared_ptr<skyway::room::sfu::LocalSFURoomMember> room_member_;
    std::unique_ptr<skyway::media::V4l2VideoRenderer> renderer_;
    std::string renderer_device_name_;
    std::vector<std::unique_ptr<std::thread>> threads_;
};

#endif  // SKYWAY_EXAMPLES_SFU_EXAMPLE_ROOM_HPP_
