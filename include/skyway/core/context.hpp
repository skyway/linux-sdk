//
//  context.hpp
//  skyway
//
//  Created by sandabu on 2021/11/08.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_CORE_CONTEXT_HPP_
#define SKYWAY_CORE_CONTEXT_HPP_

#include "skyway/core/config.hpp"
#include "skyway/core/context_options.hpp"
#include "skyway/core/interface/remote_member_plugin.hpp"
#include "skyway/global/error.hpp"
#include "skyway/global/interface/logger.hpp"
#include "skyway/network/interface/http_client.hpp"
#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/platform/interface/platform_info_delegator.hpp"
#include "skyway/rtc_api/interface/client.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace core {
namespace channel {
// forward declaration for testing
class CoreChannelTest;

}  // namespace channel
namespace ice {
class CoreIceManagerTest;
}  // namespace ice
}  // namespace core
}  // namespace skyway

namespace skyway {
namespace core {

using RemoteMemberPluginInterface     = interface::RemoteMemberPlugin;
using HttpClientInterface             = network::interface::HttpClient;
using WebSocketClientFactoryInterface = network::interface::WebSocketClientFactory;
using PlatformInfoDelegatorInterface  = platform::interface::PlatformInfoDelegator;
using LoggerInterface                 = global::interface::Logger;
using SkyWayError                     = global::Error;

/// SkyWay全体の設定、取得を行うStaticなコンテキスト
class Context {
public:
    /// イベントリスナ
    class EventListener {
    public:
        virtual ~EventListener() = default;

        /// @brief 再接続処理が開始した時にコールされます。
        virtual void OnReconnectStart() = 0;

        /// @brief 再接続が成功した時にコールされます。
        virtual void OnReconnectSuccess() = 0;

        /// @brief 回復不能なエラーが発生した時にコールされます。
        /// @details インターネット接続状況を確認した上で再度Context::Setupをコールしてください。
        /// @param error エラー
        virtual void OnFatalError(const SkyWayError& error) = 0;
    };
    /// @brief Contextを初期化します。
    /// @details libskywayを利用するためには必ずこのメソッドを最初にコールする必要があります。
    /// @param token JWT形式のAuthトークン
    /// @param http Platformで実装したHttpクライアント
    /// @param ws_factory Platformで実装したWebSocketファクトリ
    /// @param platform_info
    /// Platformで実装したデバイス情報デリゲーター。nullptrを渡すとAnalyticsが無効になります。
    /// @param logger Platformで実装したLoggerクラス
    /// @param listener イベントリスナ
    /// @param options オプション
    static bool Setup(const std::string& token,
                      std::unique_ptr<HttpClientInterface> http,
                      std::unique_ptr<WebSocketClientFactoryInterface> ws_factory,
                      std::unique_ptr<PlatformInfoDelegatorInterface> platform_info,
                      std::unique_ptr<LoggerInterface> logger,
                      EventListener* listener,
                      const ContextOptions& options);

    /// @brief JWTを更新します。
    /// @param token JWT
    static bool UpdateAuthToken(const std::string& token);

    /// @cond INTERNAL_SECTION
    /// @brief RtcConfigを更新します。このAPIは内部向けのものであり、サポート対象外です。
    /// @param rtc_config RtcConfig
    static void _UpdateRtcConfig(ContextOptions::RtcConfig rtc_config);
    /// @endcond

    /// @brief RemoteMemberPluginを登録します。
    /// @param plugin RemoteMemberPlugin
    static void RegisterPlugin(std::unique_ptr<RemoteMemberPluginInterface> plugin);

    /// @brief コンテキストを破棄し、全ての接続を切断します。
    /// @details `Context::Setup`を再度コールすることで利用可能になります。
    static void Dispose();

    /// @cond INTERNAL_SECTION
    /// @brief AuthTokenManagerを取得します。
    /// @details BridgeはこのメソッドをWrapしません。
    static std::weak_ptr<token::interface::AuthTokenManager> AuthTokenManager();

    /// @brief RtcApiClientを取得します。
    /// @details BridgeはこのメソッドをWrapしません。
    static std::weak_ptr<rtc_api::interface::Client> RtcApi();

    /// @brief Setupで入力されたオプションを取得します。
    /// @details BridgeはこのメソッドをWrapしません。
    static ContextOptions Options();

    /// @brief 登録されているRemoteMemberPluginを返します。
    /// @details BridgeはこのメソッドをWrapしません。
    static std::vector<RemoteMemberPluginInterface*> GetRemoteMemberPlugins();

    /// @brief SubtypeからPluginを検索します。
    /// @details BridgeはこのメソッドをWrapしません。
    /// @param subtype サブタイプ
    /// @return 存在する場合Pluginを返し、存在しない場合はnullptrを返します。
    static RemoteMemberPluginInterface* FindRemoteMemberPluginBySubtype(const std::string& subtype);

    /// @brief 他コンポーネントから再接続処理が開始された場合コールされます。
    /// @details BridgeはこのメソッドをWrapしません。
    static void OnReconnectStart();

    /// @brief 他コンポーネントから再接続に成功した場合コールされます。
    /// @details BridgeはこのメソッドをWrapしません。
    static void OnReconnectSuccess();

    /// @brief 他コンポーネントから致命的なエラーが発生した場合コールされます。
    /// @details BridgeはこのメソッドをWrapしません。
    /// @param error エラー
    static void OnFatalError(const SkyWayError& error);
    /// @endcond
private:
    static EventListener* listener_;
    static bool is_setup_;
    static std::mutex setup_mtx_;
    static std::shared_ptr<rtc_api::interface::Client> rtc_api_;
    static std::shared_ptr<token::interface::AuthTokenManager> token_manager_;
    static ContextOptions options_;
    static std::vector<std::unique_ptr<RemoteMemberPluginInterface>> plugins_;

public:
    /// @cond INTERNAL_SECTION
    friend class CoreContextTest;
    friend class channel::CoreChannelTest;
    friend class ice::CoreIceManagerTest;
    /// @endcond
};

}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CONTEXT_HPP_ */
