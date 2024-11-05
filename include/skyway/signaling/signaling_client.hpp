//
//  signaling_client.hpp
//  skyway
//
//  Created by sandabu on 2021/08/05.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_SIGNALING_CLIENT_HPP_
#define SKYWAY_SIGNALING_SIGNALING_CLIENT_HPP_

#include <json.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "skyway/signaling/client_event.hpp"
#include "skyway/signaling/dto/payload.hpp"
#include "skyway/signaling/dto/response.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"
#include "skyway/signaling/socket.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"
#include "skyway/global/worker.hpp"

namespace skyway {
namespace signaling {

using SignalingClientInterface         = interface::SignalingClient;
using Member                           = interface::Member;
using SocketListener                   = SocketInterface::Listener;
using AuthTokenManagerInterface        = token::interface::AuthTokenManager;
using AuthTokenManagerInternalListener = token::interface::AuthTokenManager::InternalListener;

class SignalingClient : public SignalingClientInterface,
                        public SocketListener,
                        public AuthTokenManagerInternalListener {
public:
    SignalingClient(AuthTokenManagerInterface* auth, std::unique_ptr<SocketInterface> socket);

    ~SignalingClient();

    void AddListener(SignalingClientInterface::Listener* listener) override;
    void RemoveListener(SignalingClientInterface::Listener* listener) override;
    bool Connect(SignalingClientInterface::Delegator* delegator,
                 int connectivity_check_interval_sec) override;

    dto::RequestResult Request(const Member& target,
                               const nlohmann::json& data,
                               const int timeout_sec) override;

    dto::RequestResult Request(const Member& target, const nlohmann::json& data) override;
    // SocketListener
    void OnConnectionFailed() override;
    void OnDataReceived(const nlohmann::json& data) override;

private:
    bool StartConnectivityCheck(int interval_sec);

    bool StopConnectivityCheck();

    bool Response(const Member& target,
                  const std::string& request_event_id,
                  const nlohmann::json& data);

    dto::SendResult SendEvent(const ClientEvent& event, const int timeout_sec);

    void OnAcknowledgementAccepted(const dto::incoming::EventAccepted& payload);
    void OnAcknowledgementRejected(const dto::incoming::EventRejected& payload);
    void OnRequestReceived(const dto::incoming::Request& payload);
    void OnResponseReceived(const dto::incoming::Response& payload);

    // AuthTokenManager::InternalListener
    void OnTokenUpdated(const token::AuthToken* token) override;

    AuthTokenManagerInterface* auth_;
    std::unique_ptr<SocketInterface> socket_;

    std::atomic<bool> is_sending_connectivity_check_;
    std::unique_ptr<std::thread> connectivity_check_thread_;

    std::unordered_set<SignalingClientInterface::Listener*> listeners_;
    std::mutex listeners_mtx_;

    std::mutex connectivity_check_mtx_;
    std::condition_variable connectivity_check_cv_;

    using EventId = std::string;
    std::mutex acknowledgement_results_mtx_;
    std::unordered_map<EventId, dto::SendResult> acknowledgement_results_;

    std::mutex request_results_mtx_;
    std::unordered_map<EventId, nlohmann::json> request_results_;

    SignalingClientInterface::Delegator* delegator_;

    std::unique_ptr<global::interface::Worker> worker_ = std::make_unique<skyway::global::Worker>();

public:
    friend class SignalingClientTest;
};

}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_SIGNALING_CLIENT_HPP_ */
