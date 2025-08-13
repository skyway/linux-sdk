//
//  example_room.hpp
//  skyway
//
//  Created by ogura on 2024/2/2.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_EXAMPLES_QUICKSTART_EXAMPLE_ROOM_HPP_
#define SKYWAY_EXAMPLES_QUICKSTART_EXAMPLE_ROOM_HPP_

#include <skyway/context.hpp>
#include <skyway/core/stream/remote/data_stream.hpp>
#include <skyway/media/device_manager.hpp>
#include <skyway/media/stream_factory.hpp>
#include <skyway/media/v4l2_video_renderer.hpp>
#include <skyway/room/p2p/p2p_room.hpp>

// Roomの操作を行うクラスです。
class ExampleRoom : public skyway::room::interface::Room::EventListener,
                    public skyway::core::stream::remote::RemoteDataStream::Listener {
public:
    ExampleRoom(const std::string& renderer_device_name);

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

    // Impl skyway::core::stream::remote::RemoteDataStream::Listener
    void OnData(const std::string& data) override;
    void OnDataBuffer(const uint8_t* data, size_t length) override;

private:
    // 指定のPublicationをSubscribeしているかチェックします。
    bool IsSubscribed(std::shared_ptr<skyway::room::interface::RoomPublication> publication);

    std::shared_ptr<skyway::room::p2p::P2PRoom> p2proom_;
    std::shared_ptr<skyway::room::p2p::LocalP2PRoomMember> room_member_;
    std::unique_ptr<skyway::media::V4l2VideoRenderer> renderer_;
    std::shared_ptr<skyway::core::stream::local::LocalDataStream> data_stream_;
    std::string renderer_device_name_;
    std::vector<std::unique_ptr<std::thread>> threads_;
    std::atomic<bool> is_leaving_;
};

#endif  // SKYWAY_EXAMPLES_QUICKSTART_EXAMPLE_ROOM_HPP_
