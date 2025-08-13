//
//  room_domain_factory.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/11.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
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
    virtual std::shared_ptr<RoomMember> GetOrCreateRoomMember(
        std::shared_ptr<core::interface::Member> core) = 0;

    /// LocalMemberを生成します。
    ///
    /// このAPIをコールする前に`SetRoom`をコールする必要があります。
    ///
    /// - Parameter person: Core Member
    virtual std::shared_ptr<LocalRoomMember> GetOrCreateLocalRoomMember(
        std::shared_ptr<core::interface::LocalPerson> person) = 0;

    /// RemoteMemberを生成します。
    ///
    /// このAPIをコールする前に`SetRoom`をコールする必要があります。
    ///
    /// - Parameter core: Core Member
    virtual std::shared_ptr<RemoteRoomMember> GetOrCreateRemoteRoomMember(
        std::shared_ptr<plugin::remote_person::RemotePerson> person) = 0;

    /// Publicationを生成します。
    ///
    /// - Parameter core: Core Publication
    virtual std::shared_ptr<RoomPublication> GetOrCreateRoomPublication(
        std::shared_ptr<core::interface::Publication> core) = 0;

    /// Subscriptionを生成します。
    ///
    /// - Parameter core: Core Subscription
    virtual std::shared_ptr<RoomSubscription> GetOrCreateRoomSubscription(
        std::shared_ptr<core::interface::Subscription> core) = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_FACTORY_HPP */
