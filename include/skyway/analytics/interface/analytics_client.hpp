//
//  analytics_client.hpp
//  skyway
//
//  Created by Muranaka Kei on 2023/12/08.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_ANALYTICS_INTERFACE_ANALYTICS_CLIENT_HPP_
#define SKYWAY_ANALYTICS_INTERFACE_ANALYTICS_CLIENT_HPP_

#include <future>

#include "skyway/analytics/client_event.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace analytics {
namespace interface {

/// @brief アナリティクスサーバと相互通信するクライアント
class AnalyticsClient {
public:
    struct [[deprecated]] SubscriptionStats {
        model::ContentType content_type = model::ContentType::kAudio;
        model::WebRTCStats webrtc_stats;
        SubscriptionStatsReportPayload payload;

        SubscriptionStats() = default;
        SubscriptionStats(const model::ContentType content_type,
                          const model::WebRTCStats& webrtc_stats,
                          const SubscriptionStatsReportPayload& payload);
    };

    class Delegator {
    public:
        virtual ~Delegator() = default;

        [[deprecated]] virtual std::vector<SubscriptionStats>
        GetSubscriptionStatsForAnalytics() const = 0;
    };

    struct Options {
        std::optional<std::string> analytics_domain;
        std::optional<bool> use_secure_protocol;
    };

    virtual ~AnalyticsClient() = default;

    /// @brief アナリティクスサーバとの接続処理を行います。
    /// @param delegator デリゲータのポインタ
    /// @return 正常処理完了かどうか
    virtual std::future<bool> ConnectAsync(const Delegator* const delegator) = 0;

    /// @brief
    /// アナリティクスサーバにBindingRtcPeerConnectionToSubscriptionのクライアントイベントを送信します。
    /// @return 正常処理完了かどうか
    virtual std::future<bool> SendBindingRtcPeerConnectionToSubscriptionClientEventAsync(
        const BindingRtcPeerConnectionToSubscriptionPayload& payload) = 0;

    /// @deprecated 本機能は非推奨な機能であるSubscriptionStatsReportPayloadを利用しています。
    /// @brief アナリティクスサーバにSubscriptionStatsReportのクライアントイベントを送信します。
    /// @return 正常処理完了かどうか
    [[deprecated]] virtual std::future<bool> SendSubscriptionStatsReportClientEventAsync(
        SubscriptionStats stats) = 0;

    /// @brief
    /// アナリティクスサーバにRtcPeerConnectionEventReportのクライアントイベントを送信します。
    /// @return 正常処理完了かどうか
    virtual std::future<bool> SendRtcPeerConnectionEventReportClientEventAsync(
        const RtcPeerConnectionEventReportPayload& payload) = 0;

    /// @brief
    /// アナリティクスサーバにPublicationUpdateEncodingsReportのクライアントイベントを送信します。
    /// @return 正常処理完了かどうか
    virtual std::future<bool> SendPublicationUpdateEncodingsReportClientEventAsync(
        PublicationUpdateEncodingsReportPayload payload) = 0;

    /// @brief
    /// アナリティクスサーバにSubscriptionUpdatePreferredEncodingReportのクライアントイベントを送信します。
    /// @return 正常処理完了かどうか
    virtual std::future<bool> SendSubscriptionUpdatePreferredEncodingReportClientEventAsync(
        SubscriptionUpdatePreferredEncodingReportPayload payload) = 0;

private:
    virtual std::future<bool> SendClientEventAsync(const ClientEvent& event) = 0;
};

}  // namespace interface
}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_INTERFACE_ANALYTICS_CLIENT_HPP_ */
