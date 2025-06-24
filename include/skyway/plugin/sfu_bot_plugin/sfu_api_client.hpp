//
//  sfu_api_client.hpp
//  skyway
//
//  Created by salmon on 2022/2/1.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_API_CLIENT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_API_CLIENT_HPP_

#include "skyway/core/interface/publication.hpp"
#include "skyway/network/interface/http_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/dto/response.hpp"
#include "skyway/plugin/sfu_bot_plugin/forwarding.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/sfu_options.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

using HttpClientInterface  = network::interface::HttpClient;
using SfuOptions           = sfu_options::SfuOptionsParams;

class SfuApiClient : public interface::SfuApiClient {
public:
    SfuApiClient(HttpClientInterface* http, SfuOptions sfu_options);

    std::optional<dto::CreateBotResponse> CreateBot(const std::string& app_id,
                                                      const std::string& channel_id) override;
    bool DeleteBot(const std::string& bot_id) override;

    bool Connect(const std::string& transport_id, const nlohmann::json& dtls_parameters) override;

    // For Sender
    std::optional<dto::StartForwardingResponse> StartForwarding(
        const std::string& bot_id,
        const std::shared_ptr<core::interface::Publication> publication,
        ForwardingConfigure configure) override;
    bool StopForwarding(const std::string& bot_id, const std::string& forwarding_id) override;
    std::optional<dto::ConfirmSubscriptionResponse> ConfirmSubscription(
        const std::string& forwarding_id,
        const std::string& subscription_id,
        const std::string& identifier_key) override;
    std::optional<dto::CreateProducerResponse> CreateProducer(
        const std::string& bot_id,
        const std::string& forwarding_id,
        const std::string& transport_id,
        const nlohmann::json& producer_options) override;

    // For Receiver
    std::optional<dto::GetCapabilitiesResponse> GetCapabilities(
        const std::string& bot_id,
        const std::string& publication_id,
        const std::string& origin_publication_id) override;
    std::optional<dto::CreateConsumerResponse> CreateConsumer(
        const std::string& bot_id,
        const std::string& forwarding_id,
        const nlohmann::json& rtp_capabilities,
        const std::string& subscription_id,
        const std::string& subscriber_id,
        const std::string& origin_publication_id,
        const std::optional<int> spatial_layer) override;
    std::optional<dto::ChangeConsumerLayerResponse> ChangeConsumerLayer(
        const std::string& transport_id,
        const std::string& consumer_id,
        const std::string& publication_id,
        const int spatial_layer) override;

    std::optional<dto::IceRestartResponse> IceRestart(const std::string& transport_id) override;

private:
    std::optional<HttpClientInterface::Response> Request(const std::string& path,
                                                           const std::string& method,
                                                           const nlohmann::json& body) const;
    std::string GetSfuParamsEndPoint() const;
    bool IsSuccessfulStatusCode(int status);
    bool IsClientErrorStatusCode(int status);
    bool IsServerErrorStatusCode(int status);

    HttpClientInterface* http_;
    SfuOptions sfu_options_;
};

}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_API_CLIENT_HPP_ */
