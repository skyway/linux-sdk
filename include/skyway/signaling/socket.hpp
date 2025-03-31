//
//  socket.hpp
//  skyway
//
//  Created by sandabu on 2021/08/13.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_SOCKET_HPP_
#define SKYWAY_SIGNALING_SOCKET_HPP_

#include <atomic>
#include <future>

#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/platform/interface/platform_info_delegator.hpp"
#include "skyway/signaling/config.hpp"
#include "skyway/signaling/dto/payload.hpp"
#include "skyway/signaling/interface/socket.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"
#include "skyway/global/worker.hpp"

namespace skyway {

class WebSocketIntegrationTest; // Forward declaration for testing.

namespace signaling {

using SocketInterface                = interface::Socket;
using WebSocketClientInterface       = network::interface::WebSocketClient;
using PlatformInfoDelegatorInterface = platform::interface::PlatformInfoDelegator;

const std::string kSignalingWebSocketReconnectThreadName  = "sign_reconnect";

class Socket : public SocketInterface, public WebSocketClientInterface::Listener {
public:
    Socket(const std::string& session_endpoint,
           const std::string& channel_id,
           const std::optional<std::string> channel_name,
           const std::string& member_id,
           const std::optional<std::string> member_name,
           const int connectivity_check_interval_sec,
           std::weak_ptr<token::interface::AuthTokenManager> auth,
           std::shared_ptr<WebSocketClientInterface> ws,
           const PlatformInfoDelegatorInterface* platform_info);
    ~Socket();

    void RegisterListener(SocketInterface::Listener* listener) override;

    bool Connect() override;
    bool Send(const ClientEvent& event) override;
    bool IsOpen() override;
    void Dispose() override;

    // WebSocketClientInterface::Listener
    void OnMessage(const std::string& message) override;
    void OnClose(const int code) override;
    void OnError(const int code) override;

private:
    enum class State { kReady, kConnecting, kConnected };
    bool ConnectWebSocketWithRetry();
    bool CloseWebSocket(bool updatesState = true);
    void DestroyWebSocket();

    std::string GetWebsocketUrl(const std::string& session_endpoint,
                                const std::string& channel_id,
                                const std::optional<std::string> channel_name,
                                const std::string& member_id,
                                const std::optional<std::string> member_name,
                                const int connectivity_check_interval_sec,
                                const PlatformInfoDelegatorInterface* platform_info) const;
    std::string GetRelayingServerSocketSubProtocol() const;
    void Reconnect();

    const std::string url_;
    std::weak_ptr<token::interface::AuthTokenManager> auth_;
    SocketInterface::Listener* listener_;
    std::atomic<State> state_;
    std::atomic<bool> is_open_;
    std::atomic<bool> is_disposed_;
    std::shared_ptr<WebSocketClientInterface> ws_;
    std::unique_ptr<global::interface::Worker> reconnect_worker_ = std::make_unique<global::Worker>(kSignalingWebSocketReconnectThreadName);

public:
    friend class SignalingSocketTest;
    friend class skyway::WebSocketIntegrationTest;
};

}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_SOCKET_HPP_ */
