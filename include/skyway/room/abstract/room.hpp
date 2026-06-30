//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_ABSTRACT_ROOM_HPP
#define SKYWAY_ROOM_ABSTRACT_ROOM_HPP

#include <memory>
#include <mutex>

#include <skyway/global/interface/worker.hpp>

#include "skyway/room/interface/room.hpp"
#include "skyway/room/interface/room_domain_cache_manager.hpp"
#include "skyway/room/interface/room_domain_factory.hpp"
#include "skyway/room/interface/room_subscription.hpp"

namespace skyway {
namespace room {
namespace abstract {

/// @brief Roomの操作を行う抽象クラス
class Room : public interface::Room {
public:
    virtual ~Room();
    std::string Id() override;
    std::optional<std::string> Name() override;
    std::optional<std::string> Metadata() override;
    RoomState State() override;
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
    void RunWithRoomEventListenerLock(std::function<void()> function) override;
    /// @endcond
protected:
    /// @cond INTERNAL_SECTION
    class CoreEventListenerAdapter : public core::interface::Channel::EventListener {
    public:
        CoreEventListenerAdapter(Room* outer);
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
        void OnStreamUnpublished(
            std::shared_ptr<core::interface::Publication> publication) override;
        void OnPublicationEnabled(
            std::shared_ptr<core::interface::Publication> publication) override;
        void OnPublicationDisabled(
            std::shared_ptr<core::interface::Publication> publication) override;
        void OnSubscriptionListChanged() override;
        void OnPublicationSubscribed(
            std::shared_ptr<core::interface::Subscription> subscription) override;
        void OnPublicationUnsubscribed(
            std::shared_ptr<core::interface::Subscription> subscription) override;

    private:
        Room* outer_;
    };

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

    virtual void OnClosed();
    virtual void OnMetadataUpdated(const std::string& metadata);
    virtual void OnMemberListChanged()                                           = 0;
    virtual void OnMemberJoined(std::shared_ptr<core::interface::Member> member) = 0;
    virtual void OnMemberLeft(std::shared_ptr<core::interface::Member> member)   = 0;
    virtual void OnMemberMetadataUpdated(std::shared_ptr<core::interface::Member> member,
                                         const std::string& metadata)            = 0;
    virtual void OnPublicationMetadataUpdated(
        std::shared_ptr<core::interface::Publication> publication, const std::string& metadata) = 0;
    virtual void OnPublicationListChanged()                                                     = 0;
    virtual void OnStreamPublished(std::shared_ptr<core::interface::Publication> publication)   = 0;
    virtual void OnStreamUnpublished(std::shared_ptr<core::interface::Publication> publication) = 0;
    virtual void OnPublicationEnabled(
        std::shared_ptr<core::interface::Publication> publication) = 0;
    virtual void OnPublicationDisabled(
        std::shared_ptr<core::interface::Publication> publication) = 0;
    virtual void OnSubscriptionListChanged()                       = 0;
    virtual void OnPublicationSubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) = 0;
    virtual void OnPublicationUnsubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) = 0;

    std::shared_ptr<core::interface::Channel> core_;
    std::unique_ptr<interface::RoomDomainFactory> factory_;
    std::unique_ptr<CoreEventListenerAdapter> core_event_listener_adapter_;
    std::unique_ptr<global::interface::Worker> event_worker_;

    std::mutex listener_mtx_;
    interface::Room::EventListener* listener_;
    /// @endcond

private:
    RoomState ConvertToPlatformRoomState(core::interface::ChannelState state);

    const std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomPublication>>
        room_publication_cache_manager_;
    const std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomSubscription>>
        room_subscription_cache_manager_;
    const std::shared_ptr<interface::RoomDomainCacheManager<interface::LocalRoomMember>>
        local_room_member_cache_manager_;
    const std::shared_ptr<interface::RoomDomainCacheManager<interface::RemoteRoomMember>>
        remote_room_member_cache_manager_;
};

bool EnsureSfuBotExists(std::shared_ptr<core::interface::Channel> channel);

}  // namespace abstract
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ABSTRACT_ROOM_HPP */
