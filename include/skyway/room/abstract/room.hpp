//
//  room.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/11/21.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_ABSTRACT_ROOM_HPP
#define SKYWAY_ROOM_ABSTRACT_ROOM_HPP

#include <memory>
#include "skyway/room/interface/room.hpp"
#include "skyway/room/interface/room_domain_cache_manager.hpp"
#include "skyway/room/interface/room_domain_factory.hpp"
#include "skyway/room/interface/room_subscription.hpp"

namespace skyway {
namespace room {
namespace abstract {

/// @brief Roomの操作を行う抽象クラス
class Room : public interface::Room, public core::interface::Channel::EventListener {
public:
    virtual ~Room();
    std::string Id() override;
    std::optional<std::string> Name() override;
    std::optional<std::string> Metadata() override;
    core::interface::ChannelState State() override;
    std::vector<std::shared_ptr<interface::RoomPublication>> Publications() override;
    std::vector<std::shared_ptr<interface::RoomSubscription>> Subscriptions() override;
    std::vector<std::shared_ptr<interface::RoomMember>> Members() override;
    void AddEventListener(interface::Room::EventListener* listener) override;
    void RemoveEventListener(interface::Room::EventListener* listener) override;
    bool UpdateMetadata(const std::string& metadata) override;
    bool Leave(interface::RoomMember* member) override;
    bool Close() override;
    void Dispose() override;

    /// @cond INTERNAL_SECTION
    std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomPublication>>
    GetRoomPublicationCacheManager() override;
    std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomSubscription>>
    GetRoomSubscriptionCacheManager() override;
    std::shared_ptr<interface::RoomDomainCacheManager<interface::LocalRoomMember>>
    GetLocalRoomMemberCacheManager() override;
    std::shared_ptr<interface::RoomDomainCacheManager<interface::RemoteRoomMember>>
    GetRemoteRoomMemberCacheManager() override;
    /// @endcond

protected:
    Room(std::shared_ptr<core::interface::Channel> core,
         std::unique_ptr<interface::RoomDomainFactory> factory,
         std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomPublication>>
             room_publication_cache_manager,
         std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomSubscription>>
             room_subscription_cache_manager,
         std::shared_ptr<interface::RoomDomainCacheManager<interface::LocalRoomMember>>
             local_room_member_cache_manager,
         std::shared_ptr<interface::RoomDomainCacheManager<interface::RemoteRoomMember>>
             remote_room_member_cache_manager);

    // core::interface::Channel::EventListener
    void OnClosed() override;
    void OnMetadataUpdated(const std::string& metadata) override;
    void OnMemberListChanged() override;
    void OnMemberJoined(std::shared_ptr<core::interface::Member> member) override;
    void OnMemberLeft(std::shared_ptr<core::interface::Member> member) override;
    void OnMemberMetadataUpdated(std::shared_ptr<core::interface::Member> member,
                                 const std::string& metadata) override;
    void OnPublicationMetadataUpdated(std::shared_ptr<core::interface::Publication> publication,
                                      const std::string& metadata) override;
    void OnPublicationListChanged() override;
    void OnStreamPublished(std::shared_ptr<core::interface::Publication> publication) override;
    void OnStreamUnpublished(std::shared_ptr<core::interface::Publication> publication) override;
    void OnPublicationEnabled(std::shared_ptr<core::interface::Publication> publication) override;
    void OnPublicationDisabled(std::shared_ptr<core::interface::Publication> publication) override;
    void OnSubscriptionListChanged() override;
    void OnPublicationSubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnPublicationUnsubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;

    std::shared_ptr<core::interface::Channel> core_;
    std::unique_ptr<interface::RoomDomainFactory> factory_;

    std::mutex listener_mtx_;
    interface::Room::EventListener* listener_;

private:
    const std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomPublication>>
        room_publication_cache_manager_;
    const std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomSubscription>>
        room_subscription_cache_manager_;
    const std::shared_ptr<interface::RoomDomainCacheManager<interface::LocalRoomMember>>
        local_room_member_cache_manager_;
    const std::shared_ptr<interface::RoomDomainCacheManager<interface::RemoteRoomMember>>
        remote_room_member_cache_manager_;
};

}  // namespace abstract
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ABSTRACT_ROOM_HPP */
