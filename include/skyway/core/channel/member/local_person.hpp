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

#include <string>
#include <unordered_map>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/local_person.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"

namespace skyway {
namespace core {
namespace channel {
namespace member {

using LocalStream              = interface::LocalStream;
using ChunkMessengerInterface  = interface::ChunkMessenger;
using AnalyticsClientInterface = analytics::interface::AnalyticsClient;

/// @brief LocalPersonの実装クラス
class LocalPerson : public interface::LocalPerson, public AnalyticsClientInterface::Delegator {
public:
    /// @cond INTERNAL_SECTION
    LocalPerson(std::shared_ptr<interface::Channel> channel,
                const model::Member& dto,
                std::unique_ptr<ChunkMessengerInterface> messenger,
                int keepalive_interval_sec,
                int keepalive_interval_gap_sec,
                std::unique_ptr<AnalyticsClientInterface> analytics_client);
    ~LocalPerson();

    ChunkMessengerInterface* Messenger() const override;

    AnalyticsClientInterface* AnalyticsClient() const override;
    /// @endcond

    std::shared_ptr<interface::Publication> Publish(std::shared_ptr<LocalStream> stream,
                                  interface::LocalPerson::PublicationOptions options) override;
    std::shared_ptr<interface::Subscription> Subscribe(
        const std::string& publication_id,
        const interface::LocalPerson::SubscriptionOptions& options) override;
    bool Unpublish(const std::string& publication_id) const override;
    bool Unsubscribe(const std::string& subscription_id) const override;
    /// @cond INTERNAL_SECTION
    void OnPublished(std::shared_ptr<interface::Publication> publication) override;
    void OnUnpublished(std::shared_ptr<interface::Publication> publication) override;
    void OnSubscribed(std::shared_ptr<interface::Subscription> subscription, std::shared_ptr<interface::RemoteMember> publisher) override;
    void OnUnsubscribed(std::shared_ptr<interface::Subscription> subscription, std::shared_ptr<interface::RemoteMember> publisher) override;
    void OnPublicationSubscribedByRemoteMember(std::shared_ptr<interface::Subscription> subscription,
                                               std::shared_ptr<interface::RemoteMember> subscriber) override;
    void OnPublicationUnsubscribedByRemoteMember(std::shared_ptr<interface::Subscription> subscription,
                                                 std::shared_ptr<interface::RemoteMember> subscriber) override;
    void Dispose() override;
    /// @endcond

    // AnalyticsClientInterface::Delegator
    std::vector<analytics::interface::AnalyticsClient::SubscriptionStats> GetSubscriptionStatsForAnalytics()
        const override;

private:
    void UpdateMemberTtl(const std::string& channel_id, int keepalive_interval_sec);
    void SetupTtlTimer();
    using SubscriptionId = std::string;
    using SubscriptionPair =
        std::pair<std::weak_ptr<interface::Subscription>, interface::LocalPerson::SubscriptionOptions>;

    std::unique_ptr<ChunkMessengerInterface> messenger_;
    std::mutex tmp_subscriptions_mtx_;
    std::unordered_map<SubscriptionId, SubscriptionPair> tmp_subscriptions_;
    int keepalive_interval_sec_;
    int keepalive_interval_gap_sec_;

    std::unique_ptr<AnalyticsClientInterface> analytics_client_;

    std::mutex stream_mtx_;

    std::mutex is_disposed_mtx_;
    std::condition_variable is_disposed_cv_;
    bool is_disposed_;
    std::unique_ptr<std::thread> ttl_timer_thread_;
};

}  // namespace member
}  // namespace channel
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CHANNEL_MEMBER_LOCAL_PERSON_HPP_ */
