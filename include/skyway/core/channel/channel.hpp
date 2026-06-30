//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CHANNEL_CHANNEL_HPP_
#define SKYWAY_CORE_CHANNEL_CHANNEL_HPP_

#include <atomic>
#include <functional>
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

using ChannelState = interface::ChannelState;
using ChannelInit  = model::Channel::Init;
using ChannelQuery = model::Channel::Query;

using SignalingClientDelegator = signaling::interface::SignalingClient::Delegator;

class Channel : public interface::Channel, public rtc_api::ChannelState::EventListener {
public:
    Channel(std::shared_ptr<rtc_api::interface::ChannelState> rtc_api_channel_state,
            std::unique_ptr<interface::ChunkMessengerFactory> chunk_messenger_factory);
    Channel(std::shared_ptr<rtc_api::interface::ChannelState> rtc_api_channel_state);
    ~Channel();
    void SetupDomains();

    static std::shared_ptr<Channel> Create(const ChannelInit& init);

    static std::shared_ptr<Channel> Create();

    static std::shared_ptr<Channel> Find(const ChannelQuery& query);

    static std::shared_ptr<Channel> FindOrCreate(const ChannelInit& init);

    static void DisposeAllChannels();

    void AddEventListener(interface::Channel::EventListener* listener) override;
    void RemoveEventListener(interface::Channel::EventListener* listener) override;

    std::string Id() const override;
    std::optional<std::string> Name() const override;
    std::optional<std::string> Metadata() const override;
    std::shared_ptr<interface::LocalPerson> LocalPerson() override;
    std::vector<std::shared_ptr<interface::RemoteMember>> Bots(bool active_only = true) override;
    std::vector<std::shared_ptr<interface::Member>> Members(bool active_only = true) override;
    std::vector<std::shared_ptr<interface::Publication>> Publications(
        bool active_only = true) override;
    std::vector<std::shared_ptr<interface::Subscription>> Subscriptions(
        bool active_only = true) override;
    ChannelState State() const override;

    std::shared_ptr<interface::LocalPerson> Join(const model::Member::Init& init) override;
    bool UpdateMetadata(const std::string& metadata) override;
    bool Leave(std::shared_ptr<interface::Member> member) override;
    bool Close() override;
    void Dispose(bool remove_myself_if_needed = true) override;

    std::shared_ptr<interface::Member> FindMember(const std::string& member_id,
                                                  bool active_only = true) override;
    std::shared_ptr<interface::RemoteMember> FindRemoteMember(const std::string& member_id,
                                                              bool active_only = true) override;
    std::shared_ptr<interface::Publication> FindPublication(const std::string& publication_id,
                                                            bool active_only = true) override;
    std::shared_ptr<interface::Subscription> FindSubscription(const std::string& subscription_id,
                                                              bool active_only = true) override;
    std::vector<std::shared_ptr<interface::Subscription>> GetSubscriptionsByPublicationId(
        const std::string& publication_id, bool active_only = true) override;
    std::vector<std::shared_ptr<interface::Subscription>> GetSubscriptionsBySubscriberId(
        const std::string& subscriber_id, bool active_only = true) override;
    std::vector<std::shared_ptr<interface::Publication>> GetPublicationsByPublisherId(
        const std::string& publisher_id, bool active_only = true) override;

    std::optional<model::Member> GetMemberDto(const std::string& member_id) const override;
    std::optional<model::Publication> GetPublicationDto(
        const std::string& publication_id) const override;
    std::optional<model::Subscription> GetSubscriptionDto(
        const std::string& subscription_id) const override;

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

private:
    void DispatchChannelListeners(std::function<void(interface::Channel::EventListener*)> fn);

    std::vector<std::shared_ptr<interface::LocalPerson>> LocalPersons(bool active_only = true);
    std::vector<std::shared_ptr<interface::RemoteMember>> RemoteMembers(bool active_only = true);
    std::shared_ptr<member::LocalPerson> CreateLocalPerson(const model::Member& member);
    std::shared_ptr<interface::RemoteMember> CreateRemoteMember(const model::Member& member);

    std::shared_ptr<rtc_api::interface::ChannelState> rtc_api_channel_state_;
    std::atomic<ChannelState> state_ = ChannelState::kOpened;
    std::atomic<bool> is_disposed_   = false;

    std::vector<std::shared_ptr<member::LocalPerson>> persons_;
    std::vector<std::shared_ptr<interface::RemoteMember>> remote_members_;
    std::vector<std::shared_ptr<interface::Publication>> publications_;
    std::vector<std::shared_ptr<interface::Subscription>> subscriptions_;

    std::unordered_set<interface::Channel::EventListener*> listeners_;

    std::optional<std::string> tmp_local_person_id_;
    std::optional<int> tmp_keepalive_interval_sec_;
    std::optional<int> tmp_keepalive_interval_gap_sec_;
    bool waiting_for_local_person_creation_ = false;

    std::mutex listeners_mtx_;

    std::mutex persons_mtx_;
    std::mutex remote_members_mtx_;
    std::mutex publications_mtx_;
    std::mutex subscriptions_mtx_;
    std::mutex dispose_mtx_;

    std::unique_ptr<interface::ChunkMessengerFactory> chunk_messenger_factory_;

    static std::unordered_set<std::shared_ptr<Channel>> channels_;

public:
    friend class CoreChannelTest;
};

}  // namespace channel
}  // namespace core
}  // namespace skyway

#endif
