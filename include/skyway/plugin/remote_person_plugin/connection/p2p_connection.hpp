//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_P2P_CONNECTION_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_P2P_CONNECTION_HPP_

#include <api/media_stream_interface.h>
#include <api/peer_connection_interface.h>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/plugin/remote_person_plugin/connection/dto/message.hpp"
#include "skyway/plugin/remote_person_plugin/connection/receiver.hpp"
#include "skyway/plugin/remote_person_plugin/connection/sender.hpp"
#include "skyway/signaling/interface/member.hpp"

namespace skyway {
namespace plugin {
namespace remote_person {
namespace connection {

using StreamInterface         = core::interface::Stream;
using ChunkMessengerInterface = core::interface::ChunkMessenger;
using SubscriptionId          = std::string;

const std::string kRemotePersonSendThreadName = "remo_psn_send";
const std::string kRemotePersonRecvThreadName = "remo_psn_recv";

class P2PConnection : public ChunkMessengerInterface::Listener {
public:
    P2PConnection(
        const MessageMember& remote_member,
        ChunkMessengerInterface* messenger,
        core::interface::IceManager* ice_manager,
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory);

    ~P2PConnection();

    void StartPublishing(std::shared_ptr<core::interface::Publication> publication,
                         const SubscriptionId& subscription_id);

    void StopPublishing(std::shared_ptr<core::interface::Publication> publication);

    void StartSubscribing(std::shared_ptr<core::interface::Subscription> subscription);

    void StopSubscribing(const std::string& subscription_id);

    void Close();

    void OnMessage(const nlohmann::json& message) override;

private:
    P2PConnection(const MessageMember& remote_member,
                  ChunkMessengerInterface* messenger,
                  std::shared_ptr<Sender> sender,
                  std::shared_ptr<Receiver> receiver);

    void OnProducePayloadPayloadReceived(const dto::ProducePayloadPayload& payload);
    void OnUnproducePayloadPayloadReceived(const dto::UnproducePayloadPayload& payload);
    void OnAnswerPayloadPayloadReceived(const dto::AnswerPayloadPayload& payload);
    void OnRestartIcePayloadPayloadReceived(const dto::RestartIcePayloadPayload& payload);
    void OnCandidatePayloadPayloadReceived(const dto::CandidatePayloadPayload& payload);

    MessageMember remote_member_;
    ChunkMessengerInterface* messenger_;
    std::shared_ptr<Sender> sender_;
    std::shared_ptr<Receiver> receiver_;
    std::unique_ptr<global::interface::Worker> send_worker_ =
        std::make_unique<global::Worker>(kRemotePersonSendThreadName);
    std::unique_ptr<global::interface::Worker> receive_worker_ =
        std::make_unique<global::Worker>(kRemotePersonRecvThreadName);

public:
    friend class P2PConnectionTest;
};

}  // namespace connection
}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif
