//
//  context_options.hpp
//  skyway
//
//  Created by sandabu on 2022/07/26.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
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

/// @brief Contextの`Setup`時に使用するオプション
struct ContextOptions {
    /// @brief RTCAPIサーバーへの接続に関する設定
    struct RtcApi {
        std::optional<std::string> domain;
        std::optional<bool> secure;
    };
    /// @brief ICEサーバーへの接続に関する設定
    struct IceParams {
        std::optional<std::string> domain;
        std::optional<int> version;
        std::optional<bool> secure;
        webrtc::PeerConnectionInterface::IceServers custom_ice_servers;
    };
    /// @brief Signalingサーバーへの接続に関する設定
    struct Signaling {
        std::optional<std::string> domain;
        std::optional<bool> secure;
    };

    /// @brief Analyticsサーバーへの接続に関する設定
    struct Analytics {
        std::optional<std::string> domain;
        std::optional<bool> secure;
    };
    /// @brief RTCサーバーへの接続に関する設定
    struct RtcConfig {
        std::optional<int> timeout;
        /// @brief TURN接続に関するポリシーを選択します。
        std::optional<TurnPolicy> policy;
    };
    /// @brief トークンに関する設定
    struct Token {
        std::optional<int> remind_time_sec;
        token::interface::AuthTokenManager::Listener* listener = nullptr;
    };
    RtcApi rtc_api;
    IceParams ice_params;
    Signaling signaling;
    Analytics analytics;
    RtcConfig rtc_config;
    Token token;
};

}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CONTEXT_OPTIONS_HPP_ */
