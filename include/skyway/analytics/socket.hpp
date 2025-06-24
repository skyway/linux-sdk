//
//  socket.hpp
//  skyway
//
//  Created by Muranaka Kei on 2023/11/21.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ANALYTICS_SOCKET_HPP_
#define SKYWAY_ANALYTICS_SOCKET_HPP_

#include <atomic>
#include <future>
#include <unordered_set>

#include "skyway/analytics/config.hpp"
#include "skyway/analytics/interface/socket.hpp"
#include "skyway/global/worker.hpp"
#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/platform/interface/platform_info_delegator.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {

class WebSocketIntegrationTest;  // Forward declaration for testing.

namespace analytics {

const std::string kWebSocketReconnectThreadName              = "analy_reconnect";

class Socket : public interface::Socket, public network::interface::WebSocketClient::Listener {
public:
    Socket(const std::string& session_endpoint,
           const std::string& channel_id,
           const std::optional<std::string>& channel_name,
           const std::string& member_id,
           const std::optional<std::string>& member_name,
           const std::weak_ptr<token::interface::AuthTokenManager> auth,
           const std::shared_ptr<network::interface::WebSocketClient>& ws,
           const platform::interface::PlatformInfoDelegator* platform_info,
           const int max_socket_reconnect_count   = config::MAX_SOCKET_RECONNECT_COUNT,
           const int socket_open_timeout_millisec = config::SOCKET_OPEN_TIMEOUT_MILLISEC);
    ~Socket();

    void RegisterListener(interface::Socket::Listener* listener) override;

    bool Connect() override;
    bool Send(const ClientEvent& event) override;
    bool IsOpen() const override;
    void Dispose() override;

    // network::interface::WebSocketClient::Listener
    void OnMessage(const std::string& message) override;
    void OnClose(int code) override;
    void OnError(int code) override;

private:
    enum class State { kReady, kConnecting, kConnected };

    bool ConnectWebSocketWithRetry();
    bool CloseWebSocket(bool updatesState = true);
    void DestroyWebSocket();
    bool SendCore(const ClientEvent& event);
    void SendPooledEvents();
    void OnAcknowledgeEvent(const AcknowledgePayload& payload);
    static std::string GetWebsocketUrl(
        const std::string& session_endpoint,
        const std::string& channel_id,
        const std::optional<std::string>& channel_name,
        const std::string& member_id,
        const std::optional<std::string>& member_name,
        const platform::interface::PlatformInfoDelegator* platform_info);
    std::vector<std::string> GetSubProtocols() const;
    static std::unordered_map<std::string, std::string> GetHeaders(
        const platform::interface::PlatformInfoDelegator* platform_info);
    void Reconnect();

    const std::string url_;
    const std::unordered_map<std::string, std::string> headers_;
    const std::weak_ptr<token::interface::AuthTokenManager> auth_;
    interface::Socket::Listener* listener_;
    const int max_socket_reconnect_count_;
    const int socket_open_timeout_millisec_;

    std::atomic<State> state_;
    std::atomic<bool> is_disposed_;
    std::shared_ptr<network::interface::WebSocketClient> ws_;

    std::unordered_set<ClientEvent, ClientEventHash> events_to_resend_;
    std::mutex events_to_resend_mutex_;

    std::unique_ptr<global::interface::Worker> reconnect_worker_ =
    std::make_unique<global::Worker>(kWebSocketReconnectThreadName);

public:
    friend class AnalyticsSocketTest;
    friend class AnalyticsSocketIntegrationTest;
    friend class skyway::WebSocketIntegrationTest;
};

}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_SOCKET_HPP_ */
