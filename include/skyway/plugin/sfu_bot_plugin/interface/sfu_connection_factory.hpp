//
//  sfu_connection_factory.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/08/04.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_CONNECTION_FACTORY_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_CONNECTION_FACTORY_HPP_

#include "skyway/core/context.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_connection.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport_repository.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

class SfuConnectionFactory {
public:
    virtual ~SfuConnectionFactory() = default;
    virtual std::unique_ptr<SfuConnection> Create(
        const std::string& local_person_id,
        const std::string& bot_id,
        SfuApiClient* client,
        const core::ContextOptions& options,
        webrtc::PeerConnectionInterface::IceServers ice_servers,
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
        TransportRepository* transport_repo,
        analytics::interface::AnalyticsClient* analytics_client) = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_CONNECTION_FACTORY_HPP_ */
