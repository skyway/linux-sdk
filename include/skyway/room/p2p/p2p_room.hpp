//
//  p2p_room.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/11/22.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//
#ifndef SKYWAY_ROOM_P2P_P2P_ROOM_HPP
#define SKYWAY_ROOM_P2P_P2P_ROOM_HPP

#include "skyway/room/abstract/room.hpp"
#include "skyway/room/p2p/local_p2p_room_member.hpp"
#include "skyway/room/p2p/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace p2p {

/// @cond INTERNAL_SECTION
class P2PRoomFactory : public interface::RoomFactory {
public:
    std::shared_ptr<interface::Room> Create(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomDomainFactory> domain_factory) override;
    std::shared_ptr<interface::Room> Find(
        interface::RoomQuery query,
        std::unique_ptr<interface::RoomDomainFactory> domain_factory) override;
    std::shared_ptr<interface::Room> FindOrCreate(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomDomainFactory> domain_factory) override;
};
/// @endcond

/// @brief P2PRoomの操作を行うクラス
class P2PRoom : public abstract::Room, public std::enable_shared_from_this<P2PRoom> {
public:
    P2PRoom(std::shared_ptr<core::interface::Channel> channel,
            std::unique_ptr<interface::RoomDomainFactory> factory);
    interface::RoomType Type() override;

    /// @brief P2PRoomを作成します。
    static std::shared_ptr<P2PRoom> Create(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<P2PRoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief P2PRoomを作成します。
    static std::shared_ptr<P2PRoom> Create();
    /// @brief P2PRoomの検索をします。
    static std::shared_ptr<P2PRoom> Find(
        interface::RoomQuery query,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<P2PRoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief P2PRoomの検索をし、存在しなければ作成します。
    static std::shared_ptr<P2PRoom> FindOrCreate(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<P2PRoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief P2PRoomへ参加します。
    std::shared_ptr<LocalP2PRoomMember> Join(interface::RoomMemberInitOptions options);

private:
    static std::shared_ptr<P2PRoom> CreateShared(
        std::shared_ptr<core::interface::Channel> channel,
        std::unique_ptr<interface::RoomDomainFactory> factory);

public:
    /// @cond INTERNAL_SECTION
    friend class P2PRoomFactory;
    friend class P2PRoomTest;
    friend class LocalP2PRoomMemberTest;
    /// @endcond
};

}  // namespace p2p
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_P2P_P2P_ROOM_HPP */
