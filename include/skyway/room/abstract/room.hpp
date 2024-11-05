//
//  room.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/11/21.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_ROOM_ABSTRACT_ROOM_HPP
#define SKYWAY_ROOM_ABSTRACT_ROOM_HPP

#include "skyway/room/interface/room.hpp"
#include "skyway/room/interface/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace abstract {

/// @brief Roomの操作を行う抽象クラス
class Room : public interface::Room, public core::interface::Channel::EventListener {
public:
    virtual ~Room();
    std::string Id() override;
    boost::optional<std::string> Name() override;
    boost::optional<std::string> Metadata() override;
    core::interface::ChannelState State() override;
    std::vector<std::unique_ptr<interface::RoomPublication>> Publications() override;
    std::vector<std::unique_ptr<interface::RoomSubscription>> Subscriptions() override;
    std::vector<std::unique_ptr<interface::RoomMember>> Members() override;
    void AddEventListener(interface::Room::EventListener* listener) override;
    void RemoveEventListener(interface::Room::EventListener* listener) override;
    bool UpdateMetadata(const std::string& metadata) override;
    bool Leave(interface::RoomMember* member) override;
    bool Close() override;
    void Dispose() override;

protected:
    Room(std::shared_ptr<core::interface::Channel> core,
         std::unique_ptr<interface::RoomDomainFactory> factory);
    // core::interface::Channel::EventListener
    void OnClosed() override;
    void OnMetadataUpdated(const std::string& metadata) override;
    void OnMemberListChanged() override;
    void OnMemberJoined(core::interface::Member* member) override;
    void OnMemberLeft(core::interface::Member* member) override;
    void OnMemberMetadataUpdated(core::interface::Member* member,
                                 const std::string& metadata) override;
    void OnPublicationMetadataUpdated(core::interface::Publication* publication,
                                      const std::string& metadata) override;
    void OnPublicationListChanged() override;
    void OnStreamPublished(core::interface::Publication* publication) override;
    void OnStreamUnpublished(core::interface::Publication* publication) override;
    void OnPublicationEnabled(core::interface::Publication* publication) override;
    void OnPublicationDisabled(core::interface::Publication* publication) override;
    void OnSubscriptionListChanged() override;
    void OnPublicationSubscribed(core::interface::Subscription* subscription) override;
    void OnPublicationUnsubscribed(core::interface::Subscription* subscription) override;
    void OnSubscriptionEnabled(core::interface::Subscription* subscription) override;
    void OnSubscriptionDisabled(core::interface::Subscription* subscription) override;

    std::shared_ptr<core::interface::Channel> core_;
    std::unique_ptr<interface::RoomDomainFactory> factory_;

    std::mutex listener_mtx_;
    interface::Room::EventListener* listener_;
};

}  // namespace abstract
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ABSTRACT_ROOM_HPP */
