//
//  connection_state_observer.hpp
//  skyway
//
//  Created by Hiroaki Shimono on 2023/09/27.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_CONNECTION_STATE_OBSERVER_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_CONNECTION_STATE_OBSERVER_HPP_

#include <mediasoupclient.hpp>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/connection_state.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/connection_state_observer.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace connection {

class ConnectionStateObserver : public interface::ConnectionStateObserver {
public:
    ConnectionStateObserver(
        interface::SfuApiClient* client,
        analytics::interface::AnalyticsClient* analytics_client,
        const int max_restart_ice_count          = config::kDefaultMaxRestartIceCount,
        const int check_restart_ice_time_seconds = config::kDefaultRestartIceCheckingTimeSec);
    ~ConnectionStateObserver() override;

    void AddListener(std::shared_ptr<core::ConnectionStateChangeNotifiable> listener) override;
    void RemoveListener(std::shared_ptr<core::ConnectionStateChangeNotifiable> listener) override;
    void OnConnectionStateChange(interface::Transport* transport,
                                 const std::string& connection_state) override;
    void Dispose() override;

private:
    void OnConnecting(const std::string& transport_id);
    void OnConnected(const std::string& transport_id);
    void OnCompleted(const std::string& transport_id);
    void OnClosed(const std::string& transport_id);
    void OnFailedOrDisconnected(interface::Transport* transport);

    bool WaitForReconnecting(interface::Transport* transport);
    void Reconnect(interface::Transport* transport);
    void RestartIce(interface::Transport* transport);
    void NotifyConnectionStateChanged(core::ConnectionState state, const std::string& transport_id);

    const int max_restart_ice_count_;
    const int check_restart_ice_time_seconds_;

    std::atomic<core::ConnectionState> connection_state_;

    interface::SfuApiClient* api_client_;

    analytics::interface::AnalyticsClient* analytics_client_;

    std::mutex listeners_mtx_;
    std::vector<std::weak_ptr<core::ConnectionStateChangeNotifiable>> listeners_;
    std::atomic<bool> is_reconnecting_;

    std::atomic<bool> is_disposed_ = false;

    std::mutex reconnect_threads_mtx_;
    std::vector<std::unique_ptr<std::thread>> reconnect_threads_;

public:
    friend class SfuBotPluginConnectionStateObserverTest;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_CONNECTION_STATE_OBSERVER_HPP_
