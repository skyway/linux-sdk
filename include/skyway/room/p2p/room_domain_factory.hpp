//
//  room_domain_factory.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/11.
//  Copyright © 2023 NTT Communications. All rights reserved.
//
#ifndef SKYWAY_ROOM_P2P_ROOM_DOMAIN_FACTORY_HPP
#define SKYWAY_ROOM_P2P_ROOM_DOMAIN_FACTORY_HPP

#include "skyway/room/interface/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace p2p {

class RoomDomainFactory : public interface::RoomDomainFactory {
public:
    void SetWeakRoom(std::weak_ptr<interface::Room> room) override;

    std::unique_ptr<interface::RoomMember> CreateRoomMember(core::interface::Member* core) override;

    std::unique_ptr<interface::LocalRoomMember> CreateLocalRoomMember(
        core::interface::LocalPerson* person) override;
    std::unique_ptr<interface::RemoteRoomMember> CreateRemoteRoomMember(
        plugin::remote_person::RemotePerson* person) override;

    std::unique_ptr<interface::RoomPublication> CreateRoomPublication(
        core::interface::Publication* core) override;

    std::unique_ptr<interface::RoomSubscription> CreateRoomSubscription(
        core::interface::Subscription* core) override;

private:
    std::weak_ptr<interface::Room> room_;
};

}  // namespace p2p
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_P2P_ROOM_DOMAIN_FACTORY_HPP */
