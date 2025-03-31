//
//  analytics_client.hpp
//  skyway
//
//  Created by Muranaka Kei on 2023/12/08.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_ANALYTICS_ANALYTICS_CLIENT_HPP_
#define SKYWAY_ANALYTICS_ANALYTICS_CLIENT_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/analytics/interface/socket.hpp"
#include "skyway/global/worker.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace analytics {

class AnalyticsClient : public interface::AnalyticsClient,
                        public interface::Socket::Listener,
                        public token::interface::AuthTokenManager::InternalListener {
public:
    AnalyticsClient(std::weak_ptr<token::interface::AuthTokenManager> auth, std::unique_ptr<interface::Socket> socket);

    // interface::AnalyticsClient
    ~AnalyticsClient() override;

    std::future<bool> ConnectAsync(const Delegator* const delegator) override;

    std::future<bool> SendBindingRtcPeerConnectionToSubscriptionClientEventAsync(
        const BindingRtcPeerConnectionToSubscriptionPayload& payload) override;
    std::future<bool> SendSubscriptionStatsReportClientEventAsync(
        SubscriptionStats stats) override;
    std::future<bool> SendRtcPeerConnectionEventReportClientEventAsync(
        const RtcPeerConnectionEventReportPayload& payload) override;
    std::future<bool> SendPublicationUpdateEncodingsReportClientEventAsync(
        PublicationUpdateEncodingsReportPayload payload) override;
    std::future<bool> SendSubscriptionUpdatePreferredEncodingReportClientEventAsync(
        SubscriptionUpdatePreferredEncodingReportPayload payload) override;

    // interface::Socket::Listener
    void OnConnectionFailed() override;
    void OnOpen(const OpenPayload& payload) override;

    // token::interface::AuthTokenManager::InternalListener
    void OnTokenUpdated(const token::AuthToken* token) override;

    bool IsSocketOpen() const;

private:
    class Impl;
    using VersionKey     = std::string;
    using PublicationId  = VersionKey;
    using SubscriptionId = VersionKey;

    std::future<bool> ConnectAsyncCore();

    // interface::AnalyticsClient
    std::future<bool> SendClientEventAsync(const ClientEvent& event) override;

    void StopSubscriptionStatsReportThread();
    static unsigned int RetrieveVersion(std::unordered_map<VersionKey, unsigned int>& versions,
                                        std::mutex& mutex,
                                        const VersionKey& key);

    std::unique_ptr<Impl> pimpl_;
    mutable std::mutex pimpl_mutex_;
                            
    std::weak_ptr<token::interface::AuthTokenManager> auth_;
                            
    const Delegator* delegator_;
    bool disposed_;
    std::mutex disposed_mutex_;

    std::thread connection_failed_thread_;

    std::thread subscription_stats_report_thread_;
    std::mutex subscription_stats_report_thread_mutex_;
    std::atomic<bool> should_stop_subscription_stats_report_;
    std::condition_variable subscription_stats_report_cv_;
    std::vector<OpenPayload::StatsRequest::Type> subscription_stats_request_types_;
    std::unordered_map<SubscriptionId, SubscriptionStats>
        previous_subscription_stats_;

    std::unordered_map<PublicationId, unsigned int> encodings_versions_;
    std::mutex encodings_versions_mutex_;

    std::unordered_map<SubscriptionId, unsigned int> preferred_encoding_versions_;
    std::mutex preferred_encoding_versions_mutex_;

public:
    friend class AnalyticsClientTest;
    friend class AnalyticsClientIntegrationTest;
};

const nlohmann::json::object_t MakeSubscriptionStats(
    const std::vector<OpenPayload::StatsRequest::Type>& subscription_stats_request_types,
    const interface::AnalyticsClient::SubscriptionStats& stats,
    const interface::AnalyticsClient::SubscriptionStats& previous_stats);

}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_ANALYTICS_CLIENT_HPP_ */
