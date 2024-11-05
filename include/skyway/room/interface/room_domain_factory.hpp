//
//  room_domain_factory.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/11.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_FACTORY_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_FACTORY_HPP

#include <skyway/core/interface/local_person.hpp>
#include <skyway/plugin/remote_person_plugin/remote_person.hpp>

#include "skyway/room/interface/local_room_member.hpp"
#include "skyway/room/interface/remote_room_member.hpp"
#include "skyway/room/interface/room_publication.hpp"

namespace skyway {
namespace room {
namespace interface {

/// Roomに紐づくリソースのファクトリ
class RoomDomainFactory {
public:
    virtual ~RoomDomainFactory() = default;
    /// ファクトリにRoomを登録します。
    /// TODO: MemberからRoomの依存をなくし、この関数を削除する
    ///
    /// - Parameter room: Room
    virtual void SetWeakRoom(std::weak_ptr<Room> room) = 0;

    /// Memberを生成します。
    ///
    /// このAPIをコールする前に`SetRoom`をコールする必要があります。
    ///
    /// - Parameter core: Core Member
    virtual std::unique_ptr<RoomMember> CreateRoomMember(core::interface::Member* core) = 0;

    /// LocalMemberを生成します。
    ///
    /// このAPIをコールする前に`SetRoom`をコールする必要があります。
    ///
    /// - Parameter person: Core Member
    virtual std::unique_ptr<LocalRoomMember> CreateLocalRoomMember(
        core::interface::LocalPerson* person) = 0;

    /// RemoteMemberを生成します。
    ///
    /// このAPIをコールする前に`SetRoom`をコールする必要があります。
    ///
    /// - Parameter core: Core Member
    virtual std::unique_ptr<RemoteRoomMember> CreateRemoteRoomMember(
        plugin::remote_person::RemotePerson* person) = 0;

    /// Publicationを生成します。
    ///
    /// - Parameter core: Core Publication
    virtual std::unique_ptr<RoomPublication> CreateRoomPublication(
        core::interface::Publication* core) = 0;

    /// Subscriptionを生成します。
    ///
    /// - Parameter core: Core Subscription
    virtual std::unique_ptr<RoomSubscription> CreateRoomSubscription(
        core::interface::Subscription* core) = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_FACTORY_HPP */
