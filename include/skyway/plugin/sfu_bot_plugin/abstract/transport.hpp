//
//  transport.hpp
//  skyway
//
//  Created by Muranaka Kei on 2024/03/13.
//  Copyright © 2024 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_ABSTRACT_TRANSPORT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_ABSTRACT_TRANSPORT_HPP_

#include <mediasoupclient.hpp>

#include "skyway/plugin/sfu_bot_plugin/interface/connection_state_observer.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace abstract {

class Transport : public interface::Transport {
public:
    ~Transport();

    std::string GetId() const override;
    std::string GetConnectionState() const override;
    void RestartIce(const nlohmann::json& iceParameters) override;
    void SetMediasoupTransport(mediasoupclient::Transport* transport);
    void AddConnectionStateObserverListener(std::shared_ptr<core::ConnectionStateChangeNotifiable> listener);
    void RemoveConnectionStateObserverListener(std::shared_ptr<core::ConnectionStateChangeNotifiable> listener);
    std::future<void> OnConnect(mediasoupclient::Transport* transport,
                                const nlohmann::json& dtls_parameters);
    void OnConnectionStateChange(mediasoupclient::Transport* transport,
                                 const std::string& connection_state);

protected:
    Transport(interface::SfuApiClient* client,
              std::unique_ptr<interface::ConnectionStateObserver> observer);

    mediasoupclient::Transport* transport_;

    std::mutex negotiation_mtx_;

private:
    interface::SfuApiClient* client_;
    std::unique_ptr<interface::ConnectionStateObserver> observer_;

    bool is_disposed_ = false;
    std::mutex dispose_mtx_;
};

}  // namespace abstract
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_ABSTRACT_TRANSPORT_HPP_
