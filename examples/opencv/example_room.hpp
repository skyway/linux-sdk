//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_EXAMPLES_OPENCV_EXAMPLE_ROOM_HPP_
#define SKYWAY_EXAMPLES_OPENCV_EXAMPLE_ROOM_HPP_

#include <skyway/context.hpp>
#include <skyway/core/stream/remote/data_stream.hpp>
#include <skyway/media/device_manager.hpp>
#include <skyway/media/opencv/opencv_capturer_video_source.hpp>
#include <skyway/media/opencv/opencv_video_renderer.hpp>
#include <skyway/media/stream_factory.hpp>
#include <skyway/room/p2p/p2p_room.hpp>

// Roomの操作を行うクラスです。
class ExampleRoom : public skyway::room::interface::Room::EventListener,
                    public skyway::media::opencv::OpenCVVideoRenderer::Listener {
public:
    ExampleRoom();

    // SkyWayの利用を開始します。
    bool Setup(const std::string& app_id, const std::string& secret_key);

    // P2PRoomを検索/作成し、入室します。
    bool JoinRoom(const std::string& room_name);

    // Video/Audio/DataをPublishします。
    void Publish();

    // 指定のPublicationをSubscribeします。
    bool Subscribe(std::shared_ptr<skyway::room::interface::RoomPublication> publication);

    // P2PRoomに存在するPublication全てに対してSubscribeを試みます。
    void SubscribeAll();

    // P2PRoomから退出します。
    bool LeaveRoom();

    // SkyWayの利用を終了します。
    void Dispose();

    // Impl skyway::room::interface::Room::EventListener
    void OnStreamPublished(
        std::shared_ptr<skyway::room::interface::RoomPublication> publication) override;

    // Impl skyway::media::opencv::OpenCVVideoRenderer::Listener
    void OnFrame(cv::Mat mat) override;

private:
    // 指定のPublicationをSubscribeしているかチェックします。
    bool IsSubscribed(std::shared_ptr<skyway::room::interface::RoomPublication> publication);

    std::shared_ptr<skyway::room::p2p::P2PRoom> p2proom_;
    std::shared_ptr<skyway::room::p2p::LocalP2PRoomMember> room_member_;
    std::unique_ptr<skyway::media::I420VideoRenderer> renderer_;
    std::shared_ptr<skyway::media::opencv::OpenCVCapturerVideoSource> capturer_;
    std::vector<std::unique_ptr<std::thread>> threads_;
    std::atomic<bool> is_leaving_;
};

#endif  // SKYWAY_EXAMPLES_QUICKSTART_EXAMPLE_ROOM_HPP_
