//
//  response.hpp
//  skyway
//
//  Created by salmon on 2022/03/2.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_DTO_RESPONSE_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_DTO_RESPONSE_HPP_

#include <boost/optional.hpp>
#include <json.hpp>
#include <string>

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
    boost::optional<nlohmann::json> rtp_capabilities;
    boost::optional<nlohmann::json> broadcaster_transport_options;
    std::string identifier_key;
};

struct ConfirmSubscriptionResponse {
    std::string message;
    std::string operation_id;
};

struct CreateProducerResponse {
    std::string producer_id;
    std::string transportId;
    boost::optional<nlohmann::json> transport_options;
};

struct GetCapabilitiesResponse {
    nlohmann::json rtp_capabilities;
};

struct CreateConsumerResponse {
    nlohmann::json consumer_options;
    std::string producer_id;
    std::string transport_id;
    boost::optional<nlohmann::json> transport_options;
};

struct ChangeConsumerLayerResponse {};

enum ResponseStatusCode { kOK, kCLIENT_ERROR, kSERVER_ERROR };

struct IceRestartResponse {
    ResponseStatusCode status;
    boost::optional<nlohmann::json> ice_parameters;
    boost::optional<std::string> message;
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
