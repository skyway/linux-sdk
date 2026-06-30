//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CONTEXT_OPTIONS_HPP_
#define SKYWAY_CORE_CONTEXT_OPTIONS_HPP_

#include <api/peer_connection_interface.h>

#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace core {

enum class TurnPolicy {
    kEnable,
    kDisable,
    kTurnOnly,
};

struct ContextOptions {
    struct RtcApi {
        std::optional<std::string> domain;
        std::optional<bool> secure;
    };

    struct IceParams {
        std::optional<std::string> domain;
        std::optional<int> version;
        std::optional<bool> secure;
        webrtc::PeerConnectionInterface::IceServers custom_ice_servers;
    };

    struct Signaling {
        std::optional<std::string> domain;
        std::optional<bool> secure;
    };

    struct Analytics {
        std::optional<std::string> domain;
        std::optional<bool> secure;
    };

    struct RtcConfig {
        std::optional<int> timeout;

        std::optional<TurnPolicy> policy;
    };

    struct Token {
        [[deprecated]] std::optional<int> remind_time_sec;
        std::optional<int> update_remind_sec;
        token::interface::AuthTokenManager::Listener* listener = nullptr;
    };
    RtcApi rtc_api;
    IceParams ice_params;
    Signaling signaling;
    Analytics analytics;
    RtcConfig rtc_config;
    Token token;

    bool dispose_channel_when_close = false;
};

}  // namespace core
}  // namespace skyway

#endif
