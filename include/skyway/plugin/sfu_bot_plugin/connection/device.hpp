//
//  device.hpp
//  skyway
//
//  Created by Hiroaki Shimono on 2023/09/29.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_DEVICE_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_DEVICE_HPP_

#include "skyway/plugin/sfu_bot_plugin/interface/device.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace connection {

class Device : public interface::Device {
public:
    Device();
    ~Device();

    bool IsLoaded() override;

    void Load(nlohmann::json router_rtp_capabilities,
              const mediasoupclient::PeerConnection::Options* peer_connection_options) override;

    nlohmann::json GetRtpCapabilities() override;

    std::unique_ptr<interface::SendTransport> CreateSendTransport(
        interface::SfuApiClient* client,
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const PeerConnectionOptions* pc_options) override;

    std::unique_ptr<interface::RecvTransport> CreateRecvTransport(
        interface::SfuApiClient* client,
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const PeerConnectionOptions* pc_options) override;

private:
    std::unique_ptr<mediasoupclient::Device> device_;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_DEVICE_HPP_
