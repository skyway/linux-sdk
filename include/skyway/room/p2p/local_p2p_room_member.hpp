//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_P2P_LOCAL_P2P_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_P2P_LOCAL_P2P_ROOM_MEMBER_HPP

#include "skyway/room/abstract/local_room_member.hpp"

namespace skyway {
namespace room {
namespace p2p {

/// @brief LocalRoomMemberの操作を行うクラス
class LocalP2PRoomMember : public abstract::LocalRoomMember {
public:
    LocalP2PRoomMember(std::shared_ptr<core::interface::LocalPerson> core,
                       std::shared_ptr<interface::Room> room,
                       interface::RoomDomainFactory* factory);
    ~LocalP2PRoomMember();
    std::shared_ptr<interface::RoomPublication> Publish(
        std::shared_ptr<core::interface::LocalStream> stream,
        interface::LocalRoomMember::PublicationOptions options) override;
    std::shared_ptr<interface::RoomSubscription> Subscribe(
        const std::string& publication_id,
        interface::LocalRoomMember::SubscriptionOptions options) override;
    bool Unpublish(const std::string& publication_id) override;
    bool Unsubscribe(const std::string& subscription_id) override;

private:
    std::shared_ptr<core::interface::LocalPerson> LocalPerson();
};

}  // namespace p2p
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_P2P_LOCAL_P2P_ROOM_MEMBER_HPP */
