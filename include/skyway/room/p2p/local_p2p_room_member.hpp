//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_P2P_LOCAL_P2P_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_P2P_LOCAL_P2P_ROOM_MEMBER_HPP

#include "skyway/room/abstract/local_room_member.hpp"

namespace skyway {
namespace room {
namespace p2p {

/// @deprecated 本機能は非推奨です。
/// @ref skyway::room::Room から作成した @ref skyway::room::LocalRoomMember を利用してください。
/// P2P/SFUの種別はPublish時に
/// @ref skyway::room::interface::LocalRoomMember::PublicationOptions::type で選択してください。
/// @brief LocalRoomMemberの操作を行うクラス
class [[deprecated("Use skyway::room::LocalRoomMember instead.")]] LocalP2PRoomMember
    : public abstract::LocalRoomMember {
public:
    /// @cond INTERNAL_SECTION
    LocalP2PRoomMember(std::shared_ptr<core::interface::LocalPerson> core,
                       std::shared_ptr<interface::Room> room,
                       interface::RoomDomainFactory* factory);
    /// @endcond

    ~LocalP2PRoomMember();
    std::shared_ptr<interface::RoomPublication> Publish(
        std::shared_ptr<media::stream::interface::local::LocalStream> stream,
        interface::LocalRoomMember::PublicationOptions options) override;
    std::shared_ptr<interface::RoomSubscription> Subscribe(
        const std::string& publication_id,
        interface::LocalRoomMember::SubscriptionOptions options) override;
    bool Unpublish(const std::string& publication_id) override;
    bool Unsubscribe(const std::string& subscription_id) override;
    std::vector<std::shared_ptr<interface::RoomPublication>> Publications() override;

private:
    std::shared_ptr<core::interface::LocalPerson> LocalPerson();
};

}  // namespace p2p
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_P2P_LOCAL_P2P_ROOM_MEMBER_HPP */
