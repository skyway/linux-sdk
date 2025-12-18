//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SFU_CONNECTION_FACTORY_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SFU_CONNECTION_FACTORY_HPP_

#include "skyway/plugin/sfu_bot_plugin/interface/sfu_connection_factory.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace connection {

class SfuConnectionFactory : public interface::SfuConnectionFactory {
public:
    std::unique_ptr<interface::SfuConnection> Create(
        const std::string& local_person_id,
        const std::string& bot_id,
        interface::SfuApiClient* client,
        const core::ContextOptions& options,
        webrtc::PeerConnectionInterface::IceServers ice_servers,
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
        interface::TransportRepository* transport_repo,
        analytics::interface::AnalyticsClient* analytics_client) override;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SFU_CONNECTION_FACTORY_HPP_ */
