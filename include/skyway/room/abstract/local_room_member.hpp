//
//  local_room_member.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/18.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_ROOM_ABSTRACT_LOCAL_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_ABSTRACT_LOCAL_ROOM_MEMBER_HPP

#include <skyway/core/interface/local_person.hpp>

#include "skyway/room/abstract/room_member.hpp"
#include "skyway/room/interface/local_room_member.hpp"
#include "skyway/room/interface/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace abstract {

/// @brief LocalRoomMemberの操作を行う抽象クラス
class LocalRoomMember : public abstract::RoomMember,
                        public interface::LocalRoomMember,
                        public core::interface::LocalPerson::EventListener {
public:
    virtual ~LocalRoomMember();

    /// @brief イベントの購読します。
    void AddEventListener(interface::LocalRoomMember::EventListener* listener) override;
    /// @brief イベントの購読を中止します。
    void RemoveEventListener(interface::LocalRoomMember::EventListener* listener) override;

protected:
    LocalRoomMember(core::interface::LocalPerson* core,
                    std::shared_ptr<interface::Room> room,
                    interface::RoomDomainFactory* factory);

private:
    // core::interface::LocalPerson::EventListener
    void OnStreamPublished(core::interface::Publication* publication) override;
    void OnStreamUnpublished(core::interface::Publication* publication) override;
    void OnPublicationSubscribed(core::interface::Subscription* subscription) override;
    void OnPublicationUnsubscribed(core::interface::Subscription* subscription) override;

    // core::interface::Member::EventListener
    void OnLeft() override;
    void OnMetadataUpdated(const std::string& metadata) override;
    void OnPublicationListChanged() override;
    void OnSubscriptionListChanged() override;

    std::mutex listener_mtx_;
    interface::LocalRoomMember::EventListener* listener_;
};

}  // namespace abstract
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ABSTRACT_LOCAL_ROOM_MEMBER_HPP */
