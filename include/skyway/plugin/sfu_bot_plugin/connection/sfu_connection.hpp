//
//  connection.hpp
//  skyway
//
//  Created by salmon on 2022/1/25.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SFU_CONNECTION_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SFU_CONNECTION_HPP_

#include <api/peer_connection_interface.h>

#include <mediasoupclient.hpp>
#include <unordered_map>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/context.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/stream.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/plugin/sfu_bot_plugin/connection/receiver.hpp"
#include "skyway/plugin/sfu_bot_plugin/connection/sender.hpp"
#include "skyway/plugin/sfu_bot_plugin/forwarding.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_connection.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport_repository.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace connection {

using StreamInterface       = core::interface::Stream;
using SfuApiClient          = plugin::sfu_bot::SfuApiClient;

class SfuConnection : public interface::SfuConnection {
public:
    SfuConnection(
        const std::string& local_person_id,
        const std::string& bot_id,
        interface::SfuApiClient* client,
        const core::ContextOptions& options,
        webrtc::PeerConnectionInterface::IceServers ice_servers,
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
        interface::TransportRepository* transport_repo,
        analytics::interface::AnalyticsClient* analytics_client);
    ~SfuConnection();
    std::optional<interface::StartForwardingResult> StartForwarding(
            std::shared_ptr<core::interface::Publication> publication, ForwardingConfigure configure) override;
    bool StopForwarding(Forwarding* forwarding, bool with_api_request) override;
    void StartReceiving(std::shared_ptr<core::interface::Subscription> subscription) override;
    bool StopReceiving(const std::string& subscription_id) override;

private:
    Sender* CreateSender(std::shared_ptr<core::interface::Publication> publication, ForwardingConfigure configure);
    Sender* GetSender(const std::string& publication_id);
    Receiver* CreateReceiver(std::shared_ptr<core::interface::Subscription> subscription);
    Receiver* GetReceiver(const std::string& subscription_id);

    std::string local_person_id_;
    std::string bot_id_;
    interface::SfuApiClient* client_;

    interface::TransportRepository* transport_repo_;

    analytics::interface::AnalyticsClient* analytics_client_;

    using OriginPublicationId = std::string;
    using SubscriptionId      = std::string;
    std::mutex start_forwarding_mtx_;
    std::mutex senders_mtx_;
    std::mutex receivers_mtx_;
    std::unordered_map<OriginPublicationId, std::unique_ptr<Sender>> senders_;
    std::unordered_map<SubscriptionId, std::unique_ptr<Receiver>> receivers_;

    interface::Device::PeerConnectionOptions peer_connection_options_;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SFU_CONNECTION_HPP_ */
