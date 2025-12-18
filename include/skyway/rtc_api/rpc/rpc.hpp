//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_RPC_RPC_HPP_
#define SKYWAY_RTC_API_RPC_RPC_HPP_

#include <unordered_set>

#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/rtc_api/config.hpp"
#include "skyway/rtc_api/interface/rpc.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"
#include "skyway/global/worker.hpp"

namespace skyway {
namespace rtc_api {
namespace rpc {

using RpcInterface              = interface::Rpc;
using WebSocketClientInterface  = network::interface::WebSocketClient;

const std::string kRapiReconnectThreadName = "rapi_reconnect";

/// JSON-RPCモジュール
class Rpc : public RpcInterface, public WebSocketClientInterface::Listener {
public:
    /// コンストラクタ
    Rpc(std::weak_ptr<token::interface::AuthTokenManager> auth,
        RpcInterface::Listener* listener,
        int timeout_for_send_ms = config::kDefaultTimeoutForSend);
    ~Rpc();
    bool Connect(const std::string& domain, bool secure) override;
    std::optional<nlohmann::json> Request(const std::string& method,
                                            const nlohmann::json& params,
                                            const std::string& message_id) override;
    void Close() override;
    bool IsConnected() const override;
    void AddPendingRequest(const std::string& method,
                           const nlohmann::json& params,
                           const std::string& message_id) override;

    // WebSocketClientInterface::Listener
    void OnMessage(const std::string& message) override;
    void OnClose(const int code, const std::string& reason) override;
    void OnError(const int code) override;

private:
    enum class State { kReady, kConnecting, kConnected };
    bool Send(const nlohmann::json& message) const;
    bool ConnectWebSocketWithRetry();
    void DestroyWebSocket();
    dto::RequestMessage CreateRequestMessage(const std::string& method,
                                             const nlohmann::json& params,
                                             const std::string& message_id) const;
    bool IsErrorMessage(const nlohmann::json& message) const;
    bool IsNotifyMessage(const nlohmann::json& message) const;
    std::string GetEndpoint(const std::string& domain, bool secure) const;
    std::optional<nlohmann::json> Request(dto::RequestMessage message);
    void AddPendingRequest(dto::RequestMessage message);
    void ResolvePendingRequests();
    void Reconnect();
    
    std::weak_ptr<token::interface::AuthTokenManager> auth_;
    RpcInterface::Listener* listener_;
    std::atomic<State> state_;
    std::shared_ptr<WebSocketClientInterface> ws_;
    std::string ws_domain_;
    bool is_secure_;
    std::mutex request_results_mtx_;
    using MessageId = std::string;
    // The type of value must be `dto::ResponseMessage` or `dto::ResponseErrorMessage`
    std::unordered_map<MessageId, std::optional<nlohmann::json>> request_results_;
    std::mutex request_mtx_;
    int timeout_for_send_ms_;

    std::mutex pending_requests_mtx_;
    std::unordered_set<dto::RequestMessage, dto::RequestMessage::Hash> pending_requests_;

    std::atomic<bool> disconnected_while_requesting_;
    std::atomic<bool> is_closed_;

    std::unique_ptr<global::interface::Worker> reconnect_worker_ = std::make_unique<global::Worker>(kRapiReconnectThreadName);

public:
    friend class RtcApiRpcTest;
};

}  // namespace rpc
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_RPC_RPC_HPP_ */
