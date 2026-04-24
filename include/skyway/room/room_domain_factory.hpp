//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_ROOM_DOMAIN_FACTORY_HPP
#define SKYWAY_ROOM_ROOM_DOMAIN_FACTORY_HPP

#include <mutex>

#include "skyway/room/abstract/room_domain_factory.hpp"

namespace skyway {
namespace room {

class RoomDomainFactory : public abstract::RoomDomainFactory {
public:
    std::shared_ptr<interface::LocalRoomMember> GetOrCreateLocalRoomMember(
        std::shared_ptr<core::interface::LocalPerson> person) override;

private:
    std::mutex local_room_member_mtx_;
};

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ROOM_DOMAIN_FACTORY_HPP */
