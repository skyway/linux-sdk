//
//  response.hpp
//  skyway
//
//  Created by salmon on 2022/03/2.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_DTO_RESPONSE_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_DTO_RESPONSE_HPP_

#include <string>
#include <optional>

#include <json.hpp>

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace dto {

struct CreateBotResponse {
    std::string id;
};

struct StartForwardingResponse {
    std::string forwarding_id;
    std::string broadcaster_transport_id;
    std::optional<nlohmann::json> rtp_capabilities;
    std::optional<nlohmann::json> broadcaster_transport_options;
    std::string identifier_key;
};

struct ConfirmSubscriptionResponse {
    std::string message;
    std::string operation_id;
};

struct CreateProducerResponse {
    std::string producer_id;
    std::string transportId;
    std::optional<nlohmann::json> transport_options;
};

struct GetCapabilitiesResponse {
    nlohmann::json rtp_capabilities;
};

struct CreateConsumerResponse {
    nlohmann::json consumer_options;
    std::string producer_id;
    std::string transport_id;
    std::optional<nlohmann::json> transport_options;
};

struct ChangeConsumerLayerResponse {};

enum ResponseStatusCode { kOK, kCLIENT_ERROR, kSERVER_ERROR };

struct IceRestartResponse {
    ResponseStatusCode status;
    std::optional<nlohmann::json> ice_parameters;
    std::optional<std::string> message;
};

void from_json(const nlohmann::json& j, CreateBotResponse& response);
void from_json(const nlohmann::json& j, StartForwardingResponse& response);
void from_json(const nlohmann::json& j, ConfirmSubscriptionResponse& response);
void from_json(const nlohmann::json& j, CreateProducerResponse& response);
void from_json(const nlohmann::json& j, GetCapabilitiesResponse& response);
void from_json(const nlohmann::json& j, CreateConsumerResponse& response);
void from_json(const nlohmann::json& j, ChangeConsumerLayerResponse& response);
void from_json(const nlohmann::json& j, IceRestartResponse& response);

}  // namespace dto
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_DTO_RESPONSE_HPP_ */
