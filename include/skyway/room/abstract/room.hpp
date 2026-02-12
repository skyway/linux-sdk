//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
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
