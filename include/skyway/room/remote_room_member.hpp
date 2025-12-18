//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_REMOTE_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_REMOTE_ROOM_MEMBER_HPP

#include <skyway/plugin/remote_person_plugin/remote_person.hpp>

#include "skyway/room/abstract/room_member.hpp"
#include "skyway/room/interface/remote_room_member.hpp"

namespace skyway {
namespace room {

/// @brief RemoteRoomMemberの操作を行うクラス
class RemoteRoomMember : public abstract::RoomMember, public interface::RemoteRoomMember {
public:
    RemoteRoomMember(std::shared_ptr<plugin::remote_person::RemotePerson> person,
                     std::shared_ptr<interface::Room> room,
                     interface::RoomDomainFactory* factory);
    std::shared_ptr<interface::RoomSubscription> Subscribe(
        const std::string& publication_id) override;
    bool Unsubscribe(const std::string& subscription_id) override;

private:
    std::shared_ptr<plugin::remote_person::RemotePerson> RemotePerson();
};

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_REMOTE_ROOM_MEMBER_HPP */
