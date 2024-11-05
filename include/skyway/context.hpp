//
//  context.hpp
//  skyway
//
//  Created by iorar on 2023/10/02.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CONTEXT_HPP_
#define SKYWAY_CONTEXT_HPP_

#include <skyway/core/context.hpp>
#include <skyway/core/interface/remote_member_plugin.hpp>
#include <skyway/global/error.hpp>
#include <skyway/global/interface/logger.hpp>
#include <skyway/network/interface/http_client.hpp>
#include <skyway/network/interface/websocket_client.hpp>

namespace skyway {

/// @brief アプリケーションでSkyWay全体の設定、取得を行うStaticなコンテキスト
/// @details 特別な理由がない場合はcore::Contextでなく、こちらを利用してください。
class Context : public core::Context {
public:
    static const unsigned VERSION_MAJOR = 0;
    static const unsigned VERSION_MINOR = 2;
    static const unsigned VERSION_PATCH = 1;

    /// @brief SkyWayの利用に関する設定
    struct SkyWayOptions : core::ContextOptions {
        /// @brief ログレベル
        global::interface::Logger::Level log_level = global::interface::Logger::kInfo;
        /// @brief WebRTCのログを有効にします
        bool enable_webrtc_log = false;
    };

    /// @brief Contextを初期化します。
    /// @details SkyWayを利用するためには必ずこのメソッドを最初にコールする必要があります。
    /// @param token JWT形式のAuthトークン
    /// @param listener イベントリスナ
    /// @param options オプション
    static bool Setup(const std::string& token,
                      core::Context::EventListener* listener,
                      const SkyWayOptions& options);

    /// @brief SkyWay SDK for Linuxのバージョンを取得します。
    static std::string GetVersionString();
};

}  // namespace skyway

#endif /* SKYWAY_CONTEXT_HPP_ */
