//
//  context_options.hpp
//  skyway
//
//  Created by sandabu on 2022/07/26.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_CONTEXT_OPTIONS_HPP_
#define SKYWAY_CORE_CONTEXT_OPTIONS_HPP_

#include <boost/optional.hpp>

#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace core {

using AuthTokenManagerInterface = token::interface::AuthTokenManager;

enum class TurnPolicy {
    kEnable,
    kDisable,
    kTurnOnly,
};

/// @brief Contextの`Setup`時に使用するオプション
struct ContextOptions {
    /// @brief RTCAPIサーバーへの接続に関する設定
    struct RtcApi {
        boost::optional<std::string> domain;
        boost::optional<bool> secure;
    };
    /// @brief ICEサーバーへの接続に関する設定
    struct IceParams {
        boost::optional<std::string> domain;
        boost::optional<int> version;
        boost::optional<bool> secure;
    };
    /// @brief Signalingサーバーへの接続に関する設定
    struct Signaling {
        boost::optional<std::string> domain;
        boost::optional<bool> secure;
    };

    /// @brief Analyticsサーバーへの接続に関する設定
    struct Analytics {
        boost::optional<std::string> domain;
        boost::optional<bool> secure;
    };
    /// @brief RTCサーバーへの接続に関する設定
    struct RtcConfig {
        boost::optional<int> timeout;
        /// @brief TURN接続に関するポリシーを選択します。
        boost::optional<TurnPolicy> policy;
    };
    /// @brief トークンに関する設定
    struct Token {
        boost::optional<int> remind_time_sec;
        AuthTokenManagerInterface::Listener* listener = nullptr;
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
