//
//  send_transport.hpp
//  skyway
//
//  Created by Hiroaki Shimono on 2023/09/27.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SEND_TRANSPORT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SEND_TRANSPORT_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/connection/connection_state_observer.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/send_transport.hpp"
#include "skyway/plugin/sfu_bot_plugin/sfu_api_client.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace connection {

using TransactionId = std::string;

class SfuBotPluginSendTransportTest;

class SendTransport : public interface::SendTransport {
public:
    SendTransport(interface::SfuApiClient *client,
                  analytics::interface::AnalyticsClient *analytics_client);
    ~SendTransport();

    void AddListener(const TransactionId &transaction_id,
                     interface::SendTransport::Listener *listener) override;

    void RemoveListener(const TransactionId &transaction_id) override;
    ProducerId Produce(mediasoupclient::Producer::Listener *producer_listener,
                       rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track,
                       const std::vector<webrtc::RtpEncodingParameters> *encodings,
                       const nlohmann::json *codec_options,
                       const nlohmann::json *codec,
                       const nlohmann::json &app_data) override;

    bool IsClosed(const ProducerId &producer_id) const override;
    rtc::scoped_refptr<webrtc::RtpSenderInterface> GetRtpSender(
        const ProducerId &producer_id) const override;
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack(
        const ProducerId &producer_id) const override;
    void Close(const ProducerId &producer_id) override;
    nlohmann::json GetStats(const ProducerId &producer_id) const override;
    void ReplaceTrack(const ProducerId &producer_id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track) override;

    // mediasoupclient::SendTransport::Listener
    std::future<std::string> OnProduce(mediasoupclient::SendTransport *transport,
                                       const std::string &kind,
                                       nlohmann::json rtp_parameters,
                                       const nlohmann::json &app_data) override;
    std::future<std::string> OnProduceData(mediasoupclient::SendTransport *transport,
                                           const nlohmann::json &sctp_stream_parameters,
                                           const std::string &label,
                                           const std::string &protocol,
                                           const nlohmann::json &app_data) override;
    std::future<void> OnConnect(mediasoupclient::Transport *transport,
                                const nlohmann::json &dtls_parameters) override;
    void OnConnectionStateChange(mediasoupclient::Transport *transport,
                                 const std::string &connection_state) override;

private:
    SendTransport(interface::SfuApiClient *client,
                  std::unique_ptr<interface::ConnectionStateObserver> observer);

    mediasoupclient::Producer *FindProducer(const ProducerId &producer_id) const;

    std::mutex listeners_mtx_;
    std::unordered_map<TransactionId, interface::SendTransport::Listener *> listeners_;

    mutable std::mutex producer_operation_mtx_;
    mutable std::mutex producers_mtx_;
    std::unordered_map<ProducerId, std::unique_ptr<mediasoupclient::Producer>> producers_;

public:
    friend class skyway::plugin::sfu_bot::connection::SfuBotPluginSendTransportTest;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_SEND_TRANSPORT_HPP_
