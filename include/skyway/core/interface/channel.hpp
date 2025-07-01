//
//  channel.hpp
//  skyway
//
//  Created by sandabu on 2022/01/13.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_CHANNEL_HPP_
#define SKYWAY_CORE_INTERFACE_CHANNEL_HPP_

#include "skyway/core/interface/local_person.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/model/domain.hpp"
#include "skyway/rtc_api/channel_state.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"

namespace skyway {
namespace core {
namespace interface {

/// @brief Channelの状態
enum class ChannelState { kOpened, kClosed };

/// @brief Channelのインターフェース
// `std::enable_shared_from_this<T>` is supposed to be inherited by concrete classes.
// (e.g. skyway/core/channel/channel.hpp)
// however if so, compile failed on the Android SDK that includes interfaces.
class Channel : public std::enable_shared_from_this<Channel> {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        /// @brief このChannelが閉じられた時に発生するイベント
        virtual void OnClosed() {}

        /// @brief このChannelのMetadataが更新された時に発生するイベント
        /// @param metadata Metadata
        virtual void OnMetadataUpdated(const std::string& metadata) {}

        /// @brief Member が入退出したときに発生するイベント
        /// @details OnMemberJoinedまたはOnMemberLeftがコールされた後にコールされます。
        virtual void OnMemberListChanged() {}

        /// @brief ChannelにMemberが参加した時に発生するイベント
        /// @param member 参加したMember
        virtual void OnMemberJoined(std::shared_ptr<interface::Member> member) {}

        /// @brief ChannelからMemberが退出した時に発生するイベント
        /// @param member 退出したMember
        virtual void OnMemberLeft(std::shared_ptr<interface::Member> member) {}

        /// @brief MemberのMetadataが更新された時に発生するイベント
        /// @param member 対象のMember
        /// @param metadata Metadata
        virtual void OnMemberMetadataUpdated(std::shared_ptr<interface::Member> member,
                                             const std::string& metadata) {}

        /// @brief PublicationのMetadataが更新された時に発生するイベント
        /// @param publication 対象のPublication
        /// @param metadata Metadata
        virtual void OnPublicationMetadataUpdated(
            std::shared_ptr<interface::Publication> publication, const std::string& metadata) {}

        /// @brief Publicationが作成または削除された時に発生するイベント
        /// @details OnStreamPublishedまたはOnStreamUnpublishedがコールされた後にコールされます。
        virtual void OnPublicationListChanged() {}

        /// @brief StreamがPublishされた時に発生するイベント
        /// @param publication 対象のPublication
        virtual void OnStreamPublished(std::shared_ptr<interface::Publication> publication) {}

        /// @brief StreamがUnpublishされた時に発生するイベント
        /// @param publication 対象のPublication
        virtual void OnStreamUnpublished(std::shared_ptr<interface::Publication> publication) {}

        /// @brief PublicationがEnableになった時に発生するイベント
        /// @param publication 対象のPublication
        virtual void OnPublicationEnabled(std::shared_ptr<interface::Publication> publication) {}

        /// @brief PublicationがDisableになった時に発生するイベント
        /// @param publication 対象のPublication
        virtual void OnPublicationDisabled(std::shared_ptr<interface::Publication> publication) {}

        /// @brief StreamがSubscribeまたはUnsubscribeされた時に発生するイベント
        virtual void OnSubscriptionListChanged() {}

        /// @brief PublicationがSubscribeされた時に発生するイベント
        /// @param subscription 対象のSubscription。まだstreamがsetされていない可能性があります。
        virtual void OnPublicationSubscribed(
            std::shared_ptr<interface::Subscription> subscription) {}

        /// @brief PublicationがUnsubscribeされた時に発生するイベント
        /// @param subscription 対象のSubscription
        virtual void OnPublicationUnsubscribed(
            std::shared_ptr<interface::Subscription> subscription) {}
    };

    virtual ~Channel() = default;

    /// @brief イベントを購読します。
    /// @param listener イベントリスナ
    virtual void AddEventListener(EventListener* listener) = 0;

    /// @brief イベントの購読を中止します。
    /// @param listener 対象のイベントリスナ
    virtual void RemoveEventListener(EventListener* listener) = 0;

    /// @brief Idを取得します。
    virtual std::string Id() const = 0;

    /// @brief Nameを取得します。
    virtual std::optional<std::string> Name() const = 0;

    /// @brief Metadataを取得します。
    virtual std::optional<std::string> Metadata() const = 0;

    /// @brief ChannelにJoinしているLocalPersonを取得します。
    virtual std::shared_ptr<interface::LocalPerson> LocalPerson() = 0;

    /// @brief ChannelにJoinしているBotを取得します。
    virtual std::vector<std::shared_ptr<interface::RemoteMember>> Bots(bool active_only = true) = 0;

    /// @brief ChannelにJoinしているすべてのMemberを取得します。
    /// @details このMemberはLocalPersonも含まれます。
    virtual std::vector<std::shared_ptr<interface::Member>> Members(bool active_only = true) = 0;

    /// @brief Publicationの一覧を取得します。
    virtual std::vector<std::shared_ptr<interface::Publication>> Publications(
        bool active_only = true) = 0;

    /// @brief Subscriptionの一覧を取得します。
    virtual std::vector<std::shared_ptr<interface::Subscription>> Subscriptions(
        bool active_only = true) = 0;

    /// @brief Channelの状態を取得します。
    virtual ChannelState State() const = 0;

    /// @brief ChannelにLocalPersonを追加します。
    /// @details サーバからの応答を同期的に待ち、ブロックします。
    /// @param init 初期化オプション
    virtual std::shared_ptr<interface::LocalPerson> Join(const model::Member::Init& init) = 0;

    /// @brief ChannelからMemberを退出させます。
    /// @details サーバからの応答を同期的に待ち、ブロックします。
    ///
    /// 認可されていればLocalPersonだけでなく、RemoteMemberも退出させることができます。
    ///
    /// @param member 退出させるMember
    virtual bool Leave(std::shared_ptr<interface::Member> member) = 0;

    /// @brief Channelを閉じます。
    /// @details サーバからの応答を同期的に待ち、ブロックします。
    ///
    /// `Dispose`とは異なり、Channelを閉じるとJoinしているMemberは全て退出し、Channelは破棄されます。
    ///
    /// Closeのコール後にChannelのリソースは破棄するので`Dispose`をコールする必要はありません。
    ///
    /// Close後のChannelインスタンスは利用できません。
    virtual bool Close() = 0;

    /// @brief Channelを閉じずにChannelインスタンスを無効にし、リソースを解放します。
    /// @details `Close`とは異なり、Channelは破棄しないため入室しているMemberには影響しません。
    ///
    /// Dispose後のChannelインスタンスは利用できません。
    virtual void Dispose(bool remove_myself_if_needed) = 0;

    /// @brief Metadataを更新します。
    virtual bool UpdateMetadata(const std::string& metadata) = 0;

    /// @cond INTERNAL_SECTION
    /// @brief 入室しているMemberを検索します。
    virtual std::shared_ptr<interface::Member> FindMember(const std::string& member_id,
                                                          bool active_only = true) = 0;

    /// @brief 入室しているRemoteMemberを検索します。
    virtual std::shared_ptr<interface::RemoteMember> FindRemoteMember(const std::string& member_id,
                                                                      bool active_only = true) = 0;

    /// @brief Publicationを検索します。
    virtual std::shared_ptr<interface::Publication> FindPublication(
        const std::string& publication_id, bool active_only = true) = 0;

    /// @brief Subscriptionを検索します。
    virtual std::shared_ptr<interface::Subscription> FindSubscription(
        const std::string& subscription_id, bool active_only = true) = 0;

    /// @brief PublicationのIdに紐づいたSubscriptionの一覧を取得します。
    virtual std::vector<std::shared_ptr<interface::Subscription>> GetSubscriptionsByPublicationId(
        const std::string& publication_id, bool active_only = true) = 0;

    /// @brief SubscriberのIdに紐づいたSubscriptionの一覧を取得します。
    virtual std::vector<std::shared_ptr<interface::Subscription>> GetSubscriptionsBySubscriberId(
        const std::string& subscriber_id, bool active_only = true) = 0;

    /// @brief PublisherのIdに紐づいたPublicationの一覧を取得します。
    virtual std::vector<std::shared_ptr<interface::Publication>> GetPublicationsByPublisherId(
        const std::string& publisher_id, bool active_only = true) = 0;

    virtual std::optional<model::Member> GetMemberDto(const std::string& member_id) const = 0;
    virtual std::optional<model::Publication> GetPublicationDto(
        const std::string& publication_id) const = 0;
    virtual std::optional<model::Subscription> GetSubscriptionDto(
        const std::string& subscription_id) const = 0;
    /// @endcond
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_CHANNEL_HPP_ */
