//
//  sfu_api_client.hpp
//  skyway
//
//  Created by sandabu on 2022/06/28.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_API_CLIENT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_API_CLIENT_HPP_

#include "skyway/core/interface/publication.hpp"
#include "skyway/plugin/sfu_bot_plugin/dto/response.hpp"
#include "skyway/plugin/sfu_bot_plugin/forwarding.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

class SfuApiClient {
public:
    virtual ~SfuApiClient() = default;
    // For Plugin
    virtual std::optional<dto::CreateBotResponse> CreateBot(const std::string& app_id,
                                                              const std::string& channel_id) = 0;
    virtual bool DeleteBot(const std::string& bot_id)                                        = 0;

    virtual bool Connect(const std::string& transport_id,
                         const nlohmann::json& dtls_parameters) = 0;

    // For Sender
    virtual std::optional<dto::StartForwardingResponse> StartForwarding(
        const std::string& bot_id,
        const std::shared_ptr<core::interface::Publication> publication,
        ForwardingConfigure configure)                                                       = 0;
    virtual bool StopForwarding(const std::string& bot_id, const std::string& forwarding_id) = 0;
    virtual std::optional<dto::ConfirmSubscriptionResponse> ConfirmSubscription(
        const std::string& forwarding_id,
        const std::string& subscription_id,
        const std::string& identifier_key) = 0;
    virtual std::optional<dto::CreateProducerResponse> CreateProducer(
        const std::string& bot_id,
        const std::string& forwarding_id,
        const std::string& transport_id,
        const nlohmann::json& producer_options) = 0;

    // For Receiver
    virtual std::optional<dto::GetCapabilitiesResponse> GetCapabilities(
        const std::string& bot_id,
        const std::string& publication_id,
        const std::string& origin_publication_id) = 0;
    virtual std::optional<dto::CreateConsumerResponse> CreateConsumer(
        const std::string& bot_id,
        const std::string& forwarding_id,
        const nlohmann::json& rtp_capabilities,
        const std::string& subscription_id,
        const std::string& subscriber_id,
        const std::string& origin_publication_id,
        const std::optional<int> spatial_layer) = 0;
    virtual std::optional<dto::ChangeConsumerLayerResponse> ChangeConsumerLayer(
        const std::string& transport_id,
        const std::string& consumer_id,
        const std::string& publication_id,
        const int spatial_layer) = 0;

    virtual std::optional<dto::IceRestartResponse> IceRestart(
        const std::string& transport_id) = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway
#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_API_CLIENT_HPP_ */
