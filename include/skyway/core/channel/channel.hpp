//
//  channel.hpp
//  skyway
//
//  Created by sandabu on 2021/12/23.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_CHANNEL_CHANNEL_HPP_
#define SKYWAY_CORE_CHANNEL_CHANNEL_HPP_

#include <boost/optional.hpp>
#include <string>

#include "skyway/core/channel/member/local_person.hpp"
#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/chunk_messenger_factory.hpp"
#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/rtc_api/client.hpp"
#include "skyway/rtc_api/interface/channel_state.hpp"

namespace skyway {
namespace core {
namespace channel {

using ChannelInterface      = interface::Channel;
using ChannelState          = interface::ChannelState;
using ChannelInit           = model::Channel::Init;
using ChannelQuery          = model::Channel::Query;
using MemberInterface       = interface::Member;
using PublicationInterface  = interface::Publication;
using SubscriptionInterface = interface::Subscription;
using RemoteMember          = interface::RemoteMember;

using SignalingClientDelegator = signaling::interface::SignalingClient::Delegator;

/// @brief Channelの実装クラス
class Channel : public ChannelInterface, public rtc_api::ChannelState::EventListener {
public:
    /// @cond INTERNAL_SECTION
    Channel(std::unique_ptr<rtc_api::interface::ChannelState> rtc_api_channel_state,
            std::unique_ptr<interface::ChunkMessengerFactory> chunk_messenger_factory);
    Channel(std::unique_ptr<rtc_api::interface::ChannelState> rtc_api_channel_state);
    ~Channel();
    /// @endcond

    /// @brief Channelを作成します。
    /// @details 作成するChannelが既に存在する場合はnullptrを返します。
    /// @param init 作成するChannelの情報
    static std::shared_ptr<Channel> Create(const ChannelInit& init);
    /// @brief Channelを作成します。
    static std::shared_ptr<Channel> Create();
    /// @brief 既に存在するChannelを検索します。
    /// @details Channelが存在しない場合はnullptrを返します。
    /// @param query 検索するChannelの情報
    static std::shared_ptr<Channel> Find(const ChannelQuery& query);
    /// @brief 既に存在するChannelを検索し、存在しない場合はChannelを作成します。
    /// @param init 検索、作成するChannelの情報
    static std::shared_ptr<Channel> FindOrCreate(const ChannelInit& init);
    /// @cond INTERNAL_SECTION
    /// @brief 保有する全てのChannelを`Dispose`します。
    static void DisposeAllChannels();
    /// @endcond

    void AddEventListener(interface::Channel::EventListener* listener) override;
    void RemoveEventListener(interface::Channel::EventListener* listener) override;

    std::string Id() const override;
    boost::optional<std::string> Name() const override;
    boost::optional<std::string> Metadata() const override;
    interface::LocalPerson* LocalPerson() override;
    std::vector<RemoteMember*> Bots(bool active_only = true) override;
    std::vector<MemberInterface*> Members(bool active_only = true) override;
    std::vector<PublicationInterface*> Publications(bool active_only = true) override;
    std::vector<SubscriptionInterface*> Subscriptions(bool active_only = true) override;
    ChannelState State() const override;

    interface::LocalPerson* Join(const model::Member::Init& init) override;
    bool UpdateMetadata(const std::string& metadata) override;
    bool Leave(MemberInterface* member) override;
    bool Close() override;
    void Dispose(bool remove_myself_if_needed = true) override;

    /// @cond INTERNAL_SECTION
    MemberInterface* FindMember(const std::string& member_id, bool active_only = true) override;
    RemoteMember* FindRemoteMember(const std::string& member_id, bool active_only = true) override;
    PublicationInterface* FindPublication(const std::string& publication_id,
                                          bool active_only = true) override;
    SubscriptionInterface* FindSubscription(const std::string& subscription_id,
                                            bool active_only = true) override;
    std::vector<SubscriptionInterface*> GetSubscriptionsByPublicationId(
        const std::string& publication_id, bool active_only = true) override;
    std::vector<SubscriptionInterface*> GetSubscriptionsBySubscriberId(
        const std::string& subscriber_id, bool active_only = true) override;
    std::vector<PublicationInterface*> GetPublicationsByPublisherId(
        const std::string& publisher_id, bool active_only = true) override;

    boost::optional<model::Member> GetMemberDto(const std::string& member_id) const override;
    boost::optional<model::Publication> GetPublicationDto(
        const std::string& publication_id) const override;
    boost::optional<model::Subscription> GetSubscriptionDto(
        const std::string& subscription_id) const override;

    void AddInternalEventListener(interface::Channel::InternalEventListener*) override;
    void RemoveInternalEventListener(interface::Channel::InternalEventListener*) override;

    // ChannelState::EventListener
    void OnChannelDeleted(const std::string& channel_id) override;
    void OnChannelMetadataUpdated(model::Channel* channel) override;
    void OnMemberAdded(const model::Member& member) override;
    void OnMemberRemoved(const std::string& member_id) override;
    void OnMemberMetadataUpdated(const model::Member& member) override;
    void OnStreamPublished(const model::Publication& publication) override;
    void OnStreamUnpublished(const std::string& publication_id) override;
    void OnPublicationEnabled(const model::Publication& publication) override;
    void OnPublicationDisabled(const model::Publication& publication) override;
    void OnPublicationMetadataUpdated(const model::Publication& publication) override;
    void OnPublicationSubscribed(const model::Subscription& subscription) override;
    void OnPublicationUnsubscribed(const std::string& subscription_id) override;
    void OnSubscriptionEnabled(const model::Subscription& subscription) override;
    void OnSubscriptionDisabled(const model::Subscription& subscription) override;
    /// @endcond

private:
    void SetupDomains();
    std::vector<interface::LocalPerson*> LocalPersons(bool active_only = true);
    std::vector<RemoteMember*> RemoteMembers(bool active_only = true);
    std::unique_ptr<member::LocalPerson> CreateLocalPerson(const model::Member& member);
    std::unique_ptr<RemoteMember> CreateRemoteMember(const model::Member& member);

    std::unique_ptr<rtc_api::interface::ChannelState> rtc_api_channel_state_;
    ChannelState state_;
    std::atomic<bool> disposed_;

    std::vector<std::unique_ptr<member::LocalPerson>> persons_;
    std::vector<std::unique_ptr<RemoteMember>> remote_members_;
    std::vector<std::unique_ptr<PublicationInterface>> publications_;
    std::vector<std::unique_ptr<SubscriptionInterface>> subscriptions_;

    std::unordered_set<interface::Channel::EventListener*> listeners_;
    std::unordered_set<interface::Channel::InternalEventListener*> internal_listeners_;

    boost::optional<std::string> tmp_local_person_id_;
    boost::optional<int> tmp_keepalive_interval_sec_;
    boost::optional<int> tmp_keepalive_interval_gap_sec_;
    bool waiting_for_local_person_creation_;

    std::mutex listeners_mtx_;
    // These mutexes are required because it's possible that a domain is read on one thread while it
    // is written on another thread(rtc-api)
    std::mutex persons_mtx_;
    std::mutex remote_members_mtx_;
    std::mutex publications_mtx_;
    std::mutex subscriptions_mtx_;
    std::mutex dispose_mtx_;

    std::unique_ptr<interface::ChunkMessengerFactory> chunk_messenger_factory_;

    static std::unordered_set<std::shared_ptr<Channel>> channels_;

public:
    /// @cond INTERNAL_SECTION
    friend class CoreChannelTest;
    /// @endcond
};

}  // namespace channel
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CHANNEL_CHANNEL_HPP_ */
