//
//  send_transport.hpp
//  skyway
//
//  Created by Hiroaki Shimono on 2023/09/27.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SEND_TRANSPORT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SEND_TRANSPORT_HPP_

#include "skyway/plugin/sfu_bot_plugin/abstract/transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

using ProducerId = std::string;

namespace interface {

using TransactionId = std::string;

class SendTransport : public abstract::Transport, public mediasoupclient::SendTransport::Listener {
public:
    class Listener {
    public:
        virtual std::future<std::string> OnProduce(mediasoupclient::SendTransport *transport,
                                                   const std::string &kind,
                                                   nlohmann::json rtp_parameters,
                                                   const nlohmann::json &app_data) = 0;
    };

    virtual ~SendTransport() = default;

    /// @brief リスナーを追加します。
    /// @param transaction_id トランザクションID
    /// @param listener リスナー
    virtual void AddListener(const TransactionId &transaction_id, Listener *listener) = 0;

    /// @brief リスナーを削除します。
    /// @param transaction_id リスナーに紐づくトランザクションID
    virtual void RemoveListener(const TransactionId &transaction_id) = 0;
    virtual ProducerId Produce(mediasoupclient::Producer::Listener *producer_listener,
                               rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track,
                               const std::vector<webrtc::RtpEncodingParameters> *encodings,
                               const nlohmann::json *codec_options,
                               const nlohmann::json *codec,
                               const nlohmann::json &app_data)       = 0;

    virtual bool IsClosed(const ProducerId &producer_id) const = 0;
    virtual rtc::scoped_refptr<webrtc::RtpSenderInterface> GetRtpSender(
        const ProducerId &producer_id) const = 0;
    virtual rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack(
        const ProducerId &producer_id) const                                               = 0;
    virtual void Close(const ProducerId &producer_id)                                      = 0;
    virtual nlohmann::json GetStats(const ProducerId &producer_id) const                   = 0;
    virtual void ReplaceTrack(const ProducerId &producer_id,
                              rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track) = 0;

protected:
    SendTransport(SfuApiClient *client, std::unique_ptr<ConnectionStateObserver> observer);
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SEND_TRANSPORT_HPP_
