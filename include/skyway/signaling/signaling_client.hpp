//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_SIGNALING_CLIENT_HPP_
#define SKYWAY_SIGNALING_SIGNALING_CLIENT_HPP_

#include <atomic>
#include <condition_variable>
#include <future>
#include <json.hpp>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "skyway/global/worker.hpp"
#include "skyway/signaling/client_event.hpp"
#include "skyway/signaling/dto/payload.hpp"
#include "skyway/signaling/dto/response.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"
#include "skyway/signaling/interface/socket.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace signaling {

const std::string kSignalingWebSocketThreadName = "sign_websocket";

class SignalingClient : public interface::SignalingClient,
                        public interface::Socket::Listener,
                        public token::interface::AuthTokenManager::InternalListener {
public:
    SignalingClient(std::weak_ptr<token::interface::AuthTokenManager> auth,
                    std::unique_ptr<interface::Socket> socket);

    ~SignalingClient();
    void Dispose() override;

    void InterruptBlocking(const std::string& member_id) override;
    void ResetBlocking(const std::string& member_id) override;

    bool Connect(int connectivity_check_interval_sec) override;

    void AddListener(const interface::Member& remote_member,
                     interface::SignalingClient::Listener* listener) override;
    void RemoveListener(const interface::Member& remote_member) override;
    std::future<dto::SendResult> Send(const interface::Member& target,
                                      const nlohmann::json& data,
                                      bool skip_response_wait = false) override;
    void ResolveBufferedMessages(const interface::Member& sender) override;

    void OnConnectionFailed() override;
    void OnDataReceived(const nlohmann::json& data) override;

private:
    using EventId = std::string;

    struct PendingControlEvent {
        bool IsCompleted() const { return result.has_value(); }

        std::mutex mtx;
        std::optional<dto::SendResult> result;
    };

    struct PendingRequest {
        PendingRequest(const EventId& event_id,
                       const std::string& member_id,
                       bool skip_response_wait)
            : event_id(event_id), member_id(member_id), skip_response_wait(skip_response_wait) {}

        bool IsCompleted() const { return result.has_value(); }

        std::mutex mtx;
        const EventId event_id;
        const std::string member_id;
        std::optional<dto::RequestResult> result;
        const bool skip_response_wait;
    };

    struct ListenerValue {
        interface::Member member;
        interface::SignalingClient::Listener* listener = nullptr;
        std::unique_ptr<global::interface::Worker> worker;
    };

    dto::RequestResult Request(const interface::Member& target,
                               const nlohmann::json& data,
                               const bool skip_response_wait = false);

    bool IsBlocking(const std::string& member_id);
    bool StartConnectivityCheck(int interval_sec);

    void EmitMemberEvent(const nlohmann::json& message,
                         const interface::Member& src,
                         ListenerValue& listener_value);

    bool StopConnectivityCheck();

    bool Response(const interface::Member& target,
                  const std::string& request_event_id,
                  const nlohmann::json& data);

    std::shared_ptr<int> TryEnterOperation();
    bool IsDisposing();

    bool SendSignalingMessage(const ClientEvent& event);

    dto::SendResult SendControlEvent(const ClientEvent& event, int timeout_sec);
    std::shared_ptr<PendingControlEvent> AddPendingControlEvent(const EventId& event_id);
    void CompletePendingControlEvent(const EventId& event_id, const dto::SendResult& result);

    std::shared_ptr<PendingRequest> AddPendingRequest(const EventId& event_id,
                                                      const std::string& member_id,
                                                      bool skip_response_wait);
    void InterruptPendingRequests(const std::string& member_id);

    bool CompletePendingRequest(const EventId& event_id, const dto::RequestResult& result);

    void OnAcknowledgementAccepted(const dto::incoming::EventAccepted& payload);
    void OnAcknowledgementRejected(const dto::incoming::EventRejected& payload);
    void OnRequestReceived(const dto::incoming::Request& payload);
    void OnResponseReceived(const dto::incoming::Response& payload);

    void OnTokenUpdated(const token::AuthToken* token) override;

    std::weak_ptr<token::interface::AuthTokenManager> auth_;

    std::unique_ptr<interface::Socket> socket_;

    std::atomic<bool> is_sending_connectivity_check_ = false;
    std::unique_ptr<std::thread> connectivity_check_thread_;

    std::mutex connectivity_check_mtx_;
    std::condition_variable connectivity_check_cv_;

    std::mutex pending_control_events_mtx_;
    std::unordered_map<EventId, std::shared_ptr<PendingControlEvent>> pending_control_events_;

    std::mutex pending_requests_mtx_;
    std::unordered_map<EventId, std::shared_ptr<PendingRequest>> pending_requests_;

    std::unique_ptr<global::interface::Worker> worker_ =
        std::make_unique<skyway::global::Worker>(kSignalingWebSocketThreadName);

    std::mutex interrupt_blocking_map_mtx_;
    std::unordered_map<std::string, bool> interrupt_blocking_map_;

    std::mutex lifecycle_mtx_;
    bool is_disposing_                      = false;
    std::shared_ptr<int> active_operations_ = std::make_shared<int>(0);

    using MemberId     = std::string;
    using RequestId    = std::string;
    using BufferedPair = std::pair<interface::Member, nlohmann::json>;

    std::mutex listeners_mtx_;
    std::unordered_map<MemberId, ListenerValue> listeners_;
    std::unordered_map<RequestId, std::vector<std::string>> chunk_buffer_;
    std::unordered_multimap<MemberId, BufferedPair> buffered_messages_;

    std::mutex async_futures_mtx_;
    std::vector<std::future<void>> async_futures_;

public:
    friend class SignalingClientTest;
};

}  // namespace signaling
}  // namespace skyway

#endif
