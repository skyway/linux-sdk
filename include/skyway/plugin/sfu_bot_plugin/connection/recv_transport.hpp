//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECV_TRANSPORT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECV_TRANSPORT_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/device.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/recv_transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace connection {

class RecvTransport : public interface::RecvTransport,
                      public mediasoupclient::RecvTransport::Listener {
public:
    RecvTransport(interface::SfuApiClient* client,
                  analytics::interface::AnalyticsClient* analytics_client);
    ~RecvTransport();

    // interface::RecvTransport
    ConsumerId Consume(mediasoupclient::Consumer::Listener* consumer_listener,
                       const std::string& id,
                       const std::string& producer_id,
                       const std::string& kind,
                       nlohmann::json* rtp_parameters) override;

    bool IsClosed(const ConsumerId& consumer_id) const override;
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack(
        const ConsumerId& consumer_id) const override;
    void Close(const ConsumerId& consumer_id) override;
    nlohmann::json GetStats(const ConsumerId& consumer_id) const override;

    // mediasoupclient::RecvTransport::Listener
    std::future<void> OnConnect(mediasoupclient::Transport* transport,
                                const nlohmann::json& dtls_parameters) override;
    void OnConnectionStateChange(mediasoupclient::Transport* transport,
                                 const std::string& connection_state) override;

private:
    RecvTransport(interface::SfuApiClient* client,
                  std::unique_ptr<interface::ConnectionStateObserver> observer);

    mediasoupclient::Consumer* FindConsumer(const ConsumerId& consumer_id) const;

    mutable std::mutex consumer_operation_mtx_;
    mutable std::mutex consumers_mtx_;
    std::unordered_map<ConsumerId, std::unique_ptr<mediasoupclient::Consumer>> consumers_;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECV_TRANSPORT_HPP_
