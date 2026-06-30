//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_FACTORY_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_FACTORY_HPP

#include <skyway/core/interface/local_person.hpp>
#include <skyway/plugin/remote_person_plugin/remote_person.hpp>

#include "skyway/media/stream/interface/local/local_stream.hpp"
#include "skyway/room/interface/local_room_member.hpp"
#include "skyway/room/interface/remote_room_member.hpp"
#include "skyway/room/interface/room_publication.hpp"
#include "skyway/room/interface/room_subscription.hpp"

namespace skyway {
namespace room {
namespace interface {

/// @cond INTERNAL_SECTION
class RoomDomainFactory {
public:
    virtual ~RoomDomainFactory() = default;

    virtual void SetWeakRoom(std::weak_ptr<Room> room) = 0;

    virtual std::shared_ptr<RoomMember> GetOrCreateRoomMember(
        std::shared_ptr<core::interface::Member> core) = 0;

    virtual std::shared_ptr<LocalRoomMember> GetOrCreateLocalRoomMember(
        std::shared_ptr<core::interface::LocalPerson> person) = 0;

    virtual std::shared_ptr<RemoteRoomMember> GetOrCreateRemoteRoomMember(
        std::shared_ptr<plugin::remote_person::RemotePerson> person) = 0;

    virtual std::shared_ptr<RoomPublication> GetOrCreateRoomPublication(
        std::shared_ptr<core::interface::Publication> core,
        std::shared_ptr<media::stream::interface::local::LocalStream> stream = nullptr) = 0;

    virtual std::shared_ptr<RoomSubscription> GetOrCreateRoomSubscription(
        std::shared_ptr<core::interface::Subscription> core) = 0;
};
/// @endcond

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_FACTORY_HPP */
