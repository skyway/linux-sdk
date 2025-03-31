//
//  message.hpp
//  skyway
//
//  Created by sandabu on 2021/11/11.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_DTO_MESSAGE_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_DTO_MESSAGE_HPP_

#include <string>
#include <optional>

#include <json.hpp>

namespace skyway {
namespace plugin {
namespace remote_person {
namespace connection {
namespace dto {

struct Sdp {
    std::string sdp;
    std::string type;
};

struct IceCandidate {
    std::string sdp_mid;
    int sdp_mline_index;
    std::string candidate;
};

struct ProducePayloadPayloadInfo {
    std::string publication_id;
    std::string stream_id;
    std::optional<std::string> mid;
};

struct ProducePayloadPayload {
    Sdp sdp;
    std::string publication_id;
    ProducePayloadPayloadInfo info;
};
struct ProducePayload {
    std::string kind = "senderProduceMessage";
    ProducePayloadPayload payload;
};

struct UnproducePayloadPayload {
    Sdp sdp;
    std::string publication_id;
};
struct UnproducePayload {
    std::string kind = "senderUnproduceMessage";
    UnproducePayloadPayload payload;
};

struct AnswerPayloadPayload {
    Sdp sdp;
};
struct AnswerPayload {
    std::string kind = "receiverAnswerMessage";
    AnswerPayloadPayload payload;
};

struct RestartIcePayloadPayload {
    Sdp sdp;
};
struct RestartIcePayload {
    std::string kind = "senderRestartIceMessage";
    RestartIcePayloadPayload payload;
};

struct CandidatePayloadPayload {
    IceCandidate candidate;
    std::string role;
};
struct CandidatePayload {
    std::string kind = "iceCandidateMessage";
    CandidatePayloadPayload payload;
};

struct SenderProduceMessage {
    std::string type = "signalingMessage";
    ProducePayload payload;
};

struct SenderUnproduceMessage {
    std::string type = "signalingMessage";
    UnproducePayload payload;
};

struct SenderRestartIceMessage {
    std::string type = "signalingMessage";
    RestartIcePayload payload;
};

struct ReceiverAnswerMessage {
    std::string type = "signalingMessage";
    AnswerPayload payload;
};

struct IceCandidateMessage {
    std::string type = "signalingMessage";
    CandidatePayload payload;
};

struct SendResult {
    bool is_success;
    std::optional<std::string> error_reason;
    bool IsTargetNotFound();
};

void from_json(const nlohmann::json& j, IceCandidate& candidate);
void from_json(const nlohmann::json& j, ProducePayloadPayloadInfo& info);
void from_json(const nlohmann::json& j, ProducePayloadPayload& payload);
void from_json(const nlohmann::json& j, ProducePayload& payload);
void from_json(const nlohmann::json& j, UnproducePayloadPayload& payload);
void from_json(const nlohmann::json& j, UnproducePayload& payload);
void from_json(const nlohmann::json& j, AnswerPayloadPayload& payload);
void from_json(const nlohmann::json& j, AnswerPayload& payload);
void from_json(const nlohmann::json& j, RestartIcePayloadPayload& payload);
void from_json(const nlohmann::json& j, RestartIcePayload& payload);
void from_json(const nlohmann::json& j, CandidatePayloadPayload& payload);
void from_json(const nlohmann::json& j, CandidatePayload& payload);
void from_json(const nlohmann::json& j, SenderProduceMessage& message);
void from_json(const nlohmann::json& j, SenderUnproduceMessage& message);
void from_json(const nlohmann::json& j, SenderRestartIceMessage& message);
void from_json(const nlohmann::json& j, ReceiverAnswerMessage& message);
void from_json(const nlohmann::json& j, IceCandidateMessage& message);

void to_json(nlohmann::json& j, const IceCandidate& candidate);
void to_json(nlohmann::json& j, const ProducePayloadPayloadInfo& info);
void to_json(nlohmann::json& j, const ProducePayloadPayload& payload);
void to_json(nlohmann::json& j, const ProducePayload& payload);
void to_json(nlohmann::json& j, const UnproducePayloadPayload& payload);
void to_json(nlohmann::json& j, const UnproducePayload& payload);
void to_json(nlohmann::json& j, const AnswerPayloadPayload& payload);
void to_json(nlohmann::json& j, const AnswerPayload& payload);
void to_json(nlohmann::json& j, const RestartIcePayloadPayload& payload);
void to_json(nlohmann::json& j, const RestartIcePayload& payload);
void to_json(nlohmann::json& j, const CandidatePayloadPayload& payload);
void to_json(nlohmann::json& j, const CandidatePayload& payload);
void to_json(nlohmann::json& j, const SenderProduceMessage& message);
void to_json(nlohmann::json& j, const SenderUnproduceMessage& message);
void to_json(nlohmann::json& j, const SenderRestartIceMessage& message);
void to_json(nlohmann::json& j, const ReceiverAnswerMessage& message);
void to_json(nlohmann::json& j, const IceCandidateMessage& message);

}  // namespace dto
}  // namespace connection
}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_DTO_MESSAGE_HPP_ */
