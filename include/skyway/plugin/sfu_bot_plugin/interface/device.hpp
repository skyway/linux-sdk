//
//  device.hpp
//  skyway
//
//  Created by Hiroaki Shimono on 2023/09/29.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_DEVICE_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_DEVICE_HPP_

#include <mediasoupclient.hpp>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/recv_transport.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/send_transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

class Device {
public:
    struct PeerConnectionOptions : mediasoupclient::PeerConnection::Options {};

    virtual ~Device() = default;

    virtual bool IsLoaded() = 0;

    virtual void Load(nlohmann::json router_rtp_capabilities,
                      const mediasoupclient::PeerConnection::Options* peer_connection_options) = 0;

    virtual nlohmann::json GetRtpCapabilities() = 0;

    virtual std::unique_ptr<SendTransport> CreateSendTransport(
        SfuApiClient* client,
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const PeerConnectionOptions* pc_options) = 0;

    virtual std::unique_ptr<RecvTransport> CreateRecvTransport(
        SfuApiClient* client,
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const PeerConnectionOptions* pc_options) = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_DEVICE_HPP_
