//
//  remote_room_member.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/08.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_REMOTE_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_INTERFACE_REMOTE_ROOM_MEMBER_HPP

#include "skyway/room/interface/room_member.hpp"

namespace skyway {
namespace room {
namespace interface {

/// @brief RemoteRoomMemberの操作を行うインターフェース
class RemoteRoomMember : public virtual RoomMember {
public:
    virtual ~RemoteRoomMember() = default;
    /// @brief 公開されているPublicationを購読します。
    virtual std::shared_ptr<RoomSubscription> Subscribe(const std::string& publication_id) = 0;
    /// @brief 購読しているSubscriptionの購読を解除します。
    virtual bool Unsubscribe(const std::string& subscription_id) = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_REMOTE_ROOM_MEMBER_HPP */
