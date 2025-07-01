//
//  recv_transport.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/10/10.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_RECV_TRANSPORT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_RECV_TRANSPORT_HPP_

#include "skyway/plugin/sfu_bot_plugin/abstract/transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

using ConsumerId = std::string;

namespace interface {

class RecvTransport : public abstract::Transport {
public:
    virtual ~RecvTransport() = default;

    virtual ConsumerId Consume(mediasoupclient::Consumer::Listener* consumer_listener,
                               const std::string& id,
                               const std::string& producer_id,
                               const std::string& kind,
                               nlohmann::json* rtp_parameters) = 0;

    virtual bool IsClosed(const ConsumerId& consumer_id) const = 0;
    virtual rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack(
        const ConsumerId& consumer_id) const                             = 0;
    virtual void Close(const ConsumerId& consumer_id)                    = 0;
    virtual nlohmann::json GetStats(const ConsumerId& consumer_id) const = 0;

    RecvTransport(SfuApiClient* client, std::unique_ptr<ConnectionStateObserver> observer);
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_RECV_TRANSPORT_HPP_
