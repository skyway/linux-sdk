//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_ABSTRACT_ROOM_DOMAIN_FACTORY_HPP
#define SKYWAY_ROOM_ABSTRACT_ROOM_DOMAIN_FACTORY_HPP

#include "skyway/room/interface/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace abstract {

class RoomDomainFactory : public interface::RoomDomainFactory {
public:
    void SetWeakRoom(std::weak_ptr<interface::Room> room) override;

    std::shared_ptr<interface::RoomMember> GetOrCreateRoomMember(
        std::shared_ptr<core::interface::Member> core) override;

    std::shared_ptr<interface::RemoteRoomMember> GetOrCreateRemoteRoomMember(
        std::shared_ptr<plugin::remote_person::RemotePerson> person) override;

    std::shared_ptr<interface::RoomPublication> GetOrCreateRoomPublication(
        std::shared_ptr<core::interface::Publication> core) override;

    std::shared_ptr<interface::RoomSubscription> GetOrCreateRoomSubscription(
        std::shared_ptr<core::interface::Subscription> core) override;

protected:
    std::weak_ptr<interface::Room> GetWeakRoom();

private:
    std::weak_ptr<interface::Room> room_;
    std::mutex remote_room_member_mtx_;
    std::mutex room_publication_mtx_;
    std::mutex room_subscription_mtx_;
};

}  // namespace abstract
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ABSTRACT_ROOM_DOMAIN_FACTORY_HPP */
