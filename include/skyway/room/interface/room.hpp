//
//  room.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/11/21.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_HPP

#include <skyway/core/interface/channel.hpp>

#include "skyway/room/interface/room_domain_cache_manager.hpp"
#include "skyway/room/interface/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace interface {

enum class RoomType { kP2P, kSFU };

/// @brief Roomの`Create`/`FindOrCreate`で扱うオプション
struct RoomInitOptions {
    /// @brief Name
    std::optional<std::string> name;
    /// @brief Metadata
    std::optional<std::string> metadata;
    /// @cond INTERNAL_SECTION
    model::Channel::Init ToCore() {
        model::Channel::Init core;
        core.name     = name;
        core.metadata = metadata;
        return core;
    }
    /// @endcond
};

/// @brief Roomの`Find`/`FindOrCreate`で扱うオプション
struct RoomQuery {
    /// @brief Id
    std::optional<std::string> id;
    /// @brief Name
    std::optional<std::string> name;
    /// @cond INTERNAL_SECTION
    model::Channel::Query ToCore() {
        model::Channel::Query core;
        core.id   = id;
        core.name = name;
        return core;
    }
    /// @endcond
};

/// @brief Memberの`Create`で扱うオプション
struct RoomMemberInitOptions {
    /// @brief Name
    std::optional<std::string> name;
    /// @brief Metadata
    std::optional<std::string> metadata;
    /// @brief 生存確認の間隔
    std::optional<int> keepalive_interval_sec;
    /// @brief 生存確認の間隔を超えてChannelからMemberが削除されるまでの時間
    std::optional<int> keepalive_interval_gap_sec;
    /// @cond INTERNAL_SECTION
    model::Member::Init ToCore() {
        model::Member::Init core;
        core.name                       = name;
        core.metadata                   = metadata;
        core.keepalive_interval_sec     = keepalive_interval_sec;
        core.keepalive_interval_gap_sec = keepalive_interval_gap_sec;
        return core;
    }
    /// @endcond
};

/// @brief Roomの操作を行うインターフェース
class Room {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        virtual ~EventListener() = default;
        /// @brief このRoomが閉じられた後に発生するイベント
        virtual void OnClosed() {}

        /// @brief このRoomのMetadataが更新された後に発生するイベント
        /// @param metadata Metadata
        virtual void OnMetadataUpdated(const std::string& metadata) {}

        /// @brief RoomMemberが入退出したときに発生するイベント
        /// @details OnMemberJoinedまたはOnMemberLeftがコールされた後にコールされます。
        virtual void OnMemberListChanged() {}

        /// @brief RoomにRoomMemberが参加した後に発生するイベント
        /// @param member 参加したRoomMember
        virtual void OnMemberJoined(std::shared_ptr<RoomMember> member) {}

        /// @brief RoomからRoomMemberが退出した後に発生するイベント
        /// @param member 退出したRoomMember
        virtual void OnMemberLeft(std::shared_ptr<RoomMember> member) {}

        /// @brief RoomMemberのMetadataが更新された後に発生するイベント
        /// @param member 対象のRoomMember
        /// @param metadata Metadata
        virtual void OnMemberMetadataUpdated(std::shared_ptr<RoomMember> member,
                                             const std::string& metadata) {}

        /// @brief RoomPublicationのMetadataが更新された後に発生するイベント
        /// @param publication 対象のRoomPublication
        /// @param metadata Metadata
        virtual void OnPublicationMetadataUpdated(std::shared_ptr<RoomPublication> publication,
                                                  const std::string& metadata) {}

        /// @brief RoomPublicationが作成または削除された後に発生するイベント
        /// @details OnStreamPublishedまたはOnStreamUnpublishedがコールされた後にコールされます。
        virtual void OnPublicationListChanged() {}

        /// @brief StreamがPublishされた後に発生するイベント
        /// @param publication 対象のRoomPublication
        virtual void OnStreamPublished(std::shared_ptr<RoomPublication> publication) {}

        /// @brief StreamがUnpublishされた後に発生するイベント
        /// @param publication 対象のRoomPublication
        virtual void OnStreamUnpublished(std::shared_ptr<RoomPublication> publication) {}

        /// @brief RoomPublicationがEnableになった後に発生するイベント
        /// @param publication 対象のRoomPublication
        virtual void OnPublicationEnabled(std::shared_ptr<RoomPublication> publication) {}

        /// @brief RoomPublicationがDisableになった後に発生するイベント
        /// @param publication 対象のRoomPublication
        virtual void OnPublicationDisabled(std::shared_ptr<RoomPublication> publication) {}

        /// @brief StreamがSubscribeまたはUnsubscribeされた後に発生するイベント
        virtual void OnSubscriptionListChanged() {}

        /// @brief RoomPublicationがSubscribeされた後に発生するイベント
        /// @param subscription 対象のRoomSubscription
        virtual void OnPublicationSubscribed(std::shared_ptr<RoomSubscription> subscription) {}

        /// @brief RoomPublicationがUnsubscribeされた後に発生するイベント
        /// @param subscription 対象のRoomSubscription
        virtual void OnPublicationUnsubscribed(std::shared_ptr<RoomSubscription> subscription) {}

        /// @brief RoomSubscriptionがEnableになった後に発生するイベント
        /// @param subscription 対象のRoomSubscription
        virtual void OnSubscriptionEnabled(std::shared_ptr<RoomSubscription> subscription) {}

        /// @brief RoomSubscriptionがDisableになった後に発生するイベント
        /// @param subscription 対象のRoomSubscription
        virtual void OnSubscriptionDisabled(std::shared_ptr<RoomSubscription> subscription) {}
    };
    virtual ~Room() = default;
    /// @brief Idを取得します。
    virtual std::string Id() = 0;
    /// @brief Nameを取得します。
    virtual std::optional<std::string> Name() = 0;
    /// @brief RoomのTypeを取得します。
    virtual RoomType Type() = 0;
    /// @brief Metadataを取得します。
    virtual std::optional<std::string> Metadata() = 0;
    /// @brief Stateを取得します。
    virtual core::interface::ChannelState State() = 0;
    /// @brief Roomインスタンスに紐づくPublicationの一覧を取得します。
    virtual std::vector<std::shared_ptr<RoomPublication>> Publications() = 0;
    /// @brief Roomインスタンスに紐づくSubscriptionの一覧を取得します。
    virtual std::vector<std::shared_ptr<RoomSubscription>> Subscriptions() = 0;
    /// @brief Roomインスタンスに紐づくRoomMemberの一覧を取得します。
    virtual std::vector<std::shared_ptr<RoomMember>> Members() = 0;

    /// @brief イベントを購読します。
    virtual void AddEventListener(EventListener* listener) = 0;
    /// @brief イベントの購読を中止します。
    virtual void RemoveEventListener(EventListener* listener) = 0;
    /// @brief Metadataを更新します。
    virtual bool UpdateMetadata(const std::string& metadata) = 0;
    /// @brief 指定したMemberをRoomから退室させます。
    virtual bool Leave(RoomMember* member) = 0;
    /// @brief Roomを閉じます。
    virtual bool Close() = 0;
    /// @brief Roomを破棄します。破棄されたRoomではイベントが発火しなくなります。
    virtual void Dispose() = 0;

    /// @cond INTERNAL_SECTION
    virtual std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomPublication>>
    GetRoomPublicationCacheManager() = 0;
    virtual std::shared_ptr<interface::RoomDomainCacheManager<interface::RoomSubscription>>
    GetRoomSubscriptionCacheManager() = 0;
    virtual std::shared_ptr<interface::RoomDomainCacheManager<interface::LocalRoomMember>>
    GetLocalRoomMemberCacheManager() = 0;
    virtual std::shared_ptr<interface::RoomDomainCacheManager<interface::RemoteRoomMember>>
    GetRemoteRoomMemberCacheManager() = 0;
    /// @endcond
};

/// @cond INTERNAL_SECTION
class RoomFactory {
public:
    virtual ~RoomFactory() = default;
    virtual std::shared_ptr<Room> Create(
        RoomInitOptions options, std::unique_ptr<interface::RoomDomainFactory> domain_factory) = 0;
    virtual std::shared_ptr<Room> Find(
        RoomQuery query, std::unique_ptr<interface::RoomDomainFactory> domain_factory) = 0;
    virtual std::shared_ptr<Room> FindOrCreate(
        RoomInitOptions options, std::unique_ptr<interface::RoomDomainFactory> domain_factory) = 0;
};
/// @endcond

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_HPP */
