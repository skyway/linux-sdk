//
//  local_person.hpp
//  skyway
//
//  Created by sandabu on 2022/01/12.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_CHANNEL_MEMBER_LOCAL_PERSON_HPP_
#define SKYWAY_CORE_CHANNEL_MEMBER_LOCAL_PERSON_HPP_

#include <api/peer_connection_interface.h>

#include <boost/optional.hpp>
#include <string>
#include <unordered_map>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/local_person.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"

namespace skyway {
namespace core {
namespace channel {
namespace member {

using ChannelInterface         = interface::Channel;
using PublicationInterface     = interface::Publication;
using SubscriptionInterface    = interface::Subscription;
using LocalStream              = interface::LocalStream;
using RemoteMember             = interface::RemoteMember;
using ChunkMessengerInterface  = interface::ChunkMessenger;
using AnalyticsClientInterface = analytics::interface::AnalyticsClient;

/// @brief LocalPersonの実装クラス
class LocalPerson : public interface::LocalPerson, public AnalyticsClientInterface::Delegator {
public:
    /// @cond INTERNAL_SECTION
    LocalPerson(ChannelInterface* channel,
                const model::Member& dto,
                std::unique_ptr<ChunkMessengerInterface> messenger,
                int keepalive_interval_sec,
                int keepalive_interval_gap_sec,
                std::unique_ptr<AnalyticsClientInterface> analytics_client);
    ~LocalPerson();

    ChunkMessengerInterface* Messenger() const override;

    AnalyticsClientInterface* AnalyticsClient() const override;
    /// @endcond

    PublicationInterface* Publish(std::shared_ptr<LocalStream> stream,
                                  interface::LocalPerson::PublicationOptions options) override;
    SubscriptionInterface* Subscribe(
        const std::string& publication_id,
        const interface::LocalPerson::SubscriptionOptions& options) override;
    bool Unpublish(const std::string& publication_id) const override;
    bool Unsubscribe(const std::string& subscription_id) const override;
    /// @cond INTERNAL_SECTION
    void OnPublished(PublicationInterface* publication) override;
    void OnUnpublished(PublicationInterface* publication) override;
    void OnSubscribed(SubscriptionInterface* subscription, RemoteMember* publisher) override;
    void OnUnsubscribed(SubscriptionInterface* subscription, RemoteMember* publisher) override;
    void OnPublicationSubscribedByRemoteMember(SubscriptionInterface* subscription,
                                               RemoteMember* subscriber) override;
    void OnPublicationUnsubscribedByRemoteMember(SubscriptionInterface* subscription,
                                                 RemoteMember* subscriber) override;
    void Dispose() override;
    /// @endcond

    // AnalyticsClientInterface::Delegator
    std::vector<analytics::interface::AnalyticsClient::SubscriptionStats> GetSubscriptionStatsForAnalytics()
        const override;

private:
    void UpdateMemberTtl(int keepalive_interval_sec);
    void SetupTtlTimer();
    using SubscriptionId = std::string;
    using SubscriptionPair =
        std::pair<SubscriptionInterface*, interface::LocalPerson::SubscriptionOptions>;

    std::unique_ptr<ChunkMessengerInterface> messenger_;
    std::mutex tmp_subscriptions_mtx_;
    std::unordered_map<SubscriptionId, SubscriptionPair> tmp_subscriptions_;
    int keepalive_interval_sec_;
    int keepalive_interval_gap_sec_;

    std::unique_ptr<AnalyticsClientInterface> analytics_client_;

    std::mutex stream_mtx_;

    std::mutex disposed_mtx_;
    std::condition_variable disposed_cv_;
    bool disposed_;
    std::unique_ptr<std::thread> ttl_timer_thread_;
};

}  // namespace member
}  // namespace channel
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CHANNEL_MEMBER_LOCAL_PERSON_HPP_ */
