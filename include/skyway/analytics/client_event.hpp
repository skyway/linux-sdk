//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ANALYTICS_CLIENT_EVENT_HPP_
#define SKYWAY_ANALYTICS_CLIENT_EVENT_HPP_

#include <api/peer_connection_interface.h>

#include <chrono>
#include <json.hpp>
#include <string>

#include "skyway/model/domain.hpp"

namespace skyway {
namespace analytics {
namespace constant {

static const std::string kSender   = "sender";
static const std::string kReceiver = "receiver";

}  // namespace constant

struct ClientEvent {
    std::string id;
    std::string type;
    nlohmann::json payload;

    ClientEvent(const std::string& type, const nlohmann::json& payload);

    bool operator==(const ClientEvent& rhs) const { return id == rhs.id; }
};

struct PendingClientEvent {
    ClientEvent event;
    int retry_count = 0;
    std::chrono::steady_clock::time_point next_due;

    PendingClientEvent(
            const ClientEvent& event,
            std::chrono::steady_clock::time_point next_due = std::chrono::steady_clock::now()
    ): event(event), next_due(next_due) {}
};

struct BindingRtcPeerConnectionToSubscriptionPayload {
    std::string subscription_id;
    std::string role;
    std::string rtc_peer_connection_id;
};

struct [[deprecated]] SubscriptionStatsReportPayload {
    std::string subscription_id;
    std::string role;
    nlohmann::json stats;
    std::chrono::milliseconds created_at;  // Unix Timestamp

    SubscriptionStatsReportPayload() = default;
    SubscriptionStatsReportPayload(const std::string& subscription_id,
                                   const std::string& role);
};

struct RtcPeerConnectionEventReportPayload {
    enum class Type {
        kOffer,
        kAnswer,
        kIceCandidate,
        kIceCandidateError,
        kIceConnectionStateChange,
        kIceGatheringStateChange,
        kConnectionStateChange,
        kSignalingStateChange,
        kRestartIce,
        kSkywayConnectionStateChange
    };
    struct Data {
        std::optional<std::string> offer;
        std::optional<std::string> answer;
        std::optional<std::string> candidate;
        std::optional<std::string> event;
        std::optional<std::string> ice_connection_state;
        std::optional<std::string> ice_gathering_state;
        std::optional<std::string> connection_state;
        std::optional<std::string> signaling_state;
        std::optional<std::string> skyway_connection_state;

        static std::optional<Data> Create(Type type, const std::optional<std::string>& string);
    };
    struct IceCandidateErrorEvent {
        std::string address;
        int port;
        std::string url;
        int error_code;
        std::string error_text;

        IceCandidateErrorEvent(const std::string& address,
                               int port,
                               const std::string& url,
                               int error_code,
                               const std::string& error_text);
    };

    std::string rtc_peer_connection_id;
    Type type;
    std::optional<Data> data;
    std::chrono::milliseconds created_at;  // Unix Timestamp

    RtcPeerConnectionEventReportPayload(const std::string& rtc_peer_connection_id,
                                        Type type,
                                        const std::optional<std::string>& data_string);
    RtcPeerConnectionEventReportPayload(const std::string& rtc_peer_connection_id,
                                        const IceCandidateErrorEvent& event);
    RtcPeerConnectionEventReportPayload(
        const std::string& rtc_peer_connection_id,
        webrtc::PeerConnectionInterface::IceConnectionState ice_connection_state);
    RtcPeerConnectionEventReportPayload(
        const std::string& rtc_peer_connection_id,
        webrtc::PeerConnectionInterface::IceGatheringState ice_gathering_state);
    RtcPeerConnectionEventReportPayload(
        const std::string& rtc_peer_connection_id,
        webrtc::PeerConnectionInterface::PeerConnectionState peer_connection_state);
    RtcPeerConnectionEventReportPayload(
        const std::string& rtc_peer_connection_id,
        webrtc::PeerConnectionInterface::SignalingState signaling_state);
};

struct PublicationUpdateEncodingsReportPayload {
    std::string publication_id;
    std::vector<model::Encoding> encodings;
    unsigned int encodings_version = 0;
    std::chrono::milliseconds updated_at;  // Unix Timestamp

    PublicationUpdateEncodingsReportPayload(const std::string& publication_id,
                                            const std::vector<model::Encoding>& encodings);
};

struct SubscriptionUpdatePreferredEncodingReportPayload {
    std::string subscription_id;
    unsigned int preferred_encoding_index   = 0;
    unsigned int preferred_encoding_version = 0;
    std::chrono::milliseconds updated_at;  // Unix Timestamp

    SubscriptionUpdatePreferredEncodingReportPayload(const std::string& subscription_id,
                                                     unsigned int preferred_encoding_index);
};

void to_json(nlohmann::json& j, const ClientEvent& event);
void to_json(nlohmann::json& j, const BindingRtcPeerConnectionToSubscriptionPayload& payload);
/// @deprecated 本機能は非推奨な機能であるSubscriptionStatsReportPayloadを利用しています。
[[deprecated]] void to_json(nlohmann::json& j, const SubscriptionStatsReportPayload& payload);
void to_json(nlohmann::json& j, const RtcPeerConnectionEventReportPayload& payload);
void to_json(nlohmann::json& j, const RtcPeerConnectionEventReportPayload::Data& data);
void to_json(nlohmann::json& j,
             const RtcPeerConnectionEventReportPayload::IceCandidateErrorEvent& event);
void to_json(nlohmann::json& j, const PublicationUpdateEncodingsReportPayload& payload);
void to_json(nlohmann::json& j, const SubscriptionUpdatePreferredEncodingReportPayload& payload);

}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_CLIENT_EVENT_HPP_ */
