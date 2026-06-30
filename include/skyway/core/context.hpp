//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CONTEXT_HPP_
#define SKYWAY_CORE_CONTEXT_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/context_options.hpp"
#include "skyway/core/interface/remote_member_plugin.hpp"
#include "skyway/global/error.hpp"
#include "skyway/global/interface/logger.hpp"
#include "skyway/global/worker.hpp"
#include "skyway/network/interface/http_client.hpp"
#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/platform/interface/platform_info_delegator.hpp"
#include "skyway/rtc_api/interface/client.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace core {
namespace channel {

class CoreChannelTest;

}
namespace ice {
class CoreIceManagerTest;
}

class CorePublicationTest;
class CoreSubscriptionTest;
}  // namespace core

namespace plugin {
namespace remote_person {
namespace connection {
class RemotePersonPluginReceiverTest;
class RemotePersonPluginSenderTest;
}  // namespace connection
}  // namespace remote_person

namespace sfu_bot {
class SfuBotTest;
namespace connection {
class SfuBotPluginConnectionStateObserverTest;
class SfuBotPluginSfuConnectionTest;
class SfuBotPluginSenderTest;
}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin

}  // namespace skyway

namespace skyway {
namespace core {

using RemoteMemberPluginInterface     = interface::RemoteMemberPlugin;
using HttpClientInterface             = network::interface::HttpClient;
using WebSocketClientFactoryInterface = network::interface::WebSocketClientFactory;
using PlatformInfoDelegatorInterface  = platform::interface::PlatformInfoDelegator;
using LoggerInterface                 = global::interface::Logger;
using SkyWayError                     = global::Error;

class Context {
public:
    class EventListener {
    public:
        virtual ~EventListener() = default;

        virtual void OnReconnectStart() = 0;

        virtual void OnReconnectSuccess() = 0;

        virtual void OnFatalError(const SkyWayError& error) = 0;
    };

    static bool Setup(const std::string& token,
                      std::unique_ptr<HttpClientInterface> http,
                      std::unique_ptr<WebSocketClientFactoryInterface> ws_factory,
                      std::unique_ptr<PlatformInfoDelegatorInterface> platform_info,
                      std::unique_ptr<LoggerInterface> logger,
                      EventListener* listener,
                      const ContextOptions& options);

    static bool UpdateAuthToken(const std::string& token);

    static void _UpdateRtcConfig(ContextOptions::RtcConfig rtc_config);

    static void RegisterPlugin(std::unique_ptr<RemoteMemberPluginInterface> plugin);

    static void Dispose();

    static std::weak_ptr<token::interface::AuthTokenManager> AuthTokenManager();

    static std::weak_ptr<rtc_api::interface::Client> RtcApi();

    static std::weak_ptr<analytics::interface::AnalyticsClient> AnalyticsClient();

    static ContextOptions Options();

    static std::vector<RemoteMemberPluginInterface*> GetRemoteMemberPlugins();

    static RemoteMemberPluginInterface* FindRemoteMemberPluginBySubtype(const std::string& subtype);

    static void OnReconnectStart();

    static void OnReconnectSuccess();

    static void OnFatalError(const SkyWayError& error);

    static std::string GetContextId();

    static void PostCallback(std::function<void()> task);

private:
    static std::mutex listener_mtx_;
    static EventListener* listener_;
    static bool is_setup_;
    static std::mutex setup_mtx_;
    static std::shared_ptr<rtc_api::interface::Client> rtc_api_;
    static std::shared_ptr<token::interface::AuthTokenManager> token_manager_;
    static std::string context_id_;
    static std::shared_ptr<analytics::interface::AnalyticsClient> analytics_client_;
    static ContextOptions options_;
    static std::vector<std::unique_ptr<RemoteMemberPluginInterface>> plugins_;
    static std::mutex callback_worker_mtx_;
    static std::unique_ptr<global::Worker> callback_worker_;

public:
    friend class CoreContextTest;
    friend class CorePublicationTest;
    friend class CoreSubscriptionTest;
    friend class channel::CoreChannelTest;
    friend class ice::CoreIceManagerTest;
    friend class plugin::sfu_bot::SfuBotTest;
    friend class plugin::sfu_bot::connection::SfuBotPluginConnectionStateObserverTest;
    friend class plugin::sfu_bot::connection::SfuBotPluginSfuConnectionTest;
    friend class plugin::sfu_bot::connection::SfuBotPluginSenderTest;
    friend class plugin::remote_person::connection::RemotePersonPluginReceiverTest;
    friend class plugin::remote_person::connection::RemotePersonPluginSenderTest;
};

}  // namespace core
}  // namespace skyway

#endif
