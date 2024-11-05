//
//  connection_state_observer.hpp
//  skyway
//
//  Created by Hiroaki Shimono on 2023/10/06.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_CONNECTION_STATE_OBSERVER_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_CONNECTION_STATE_OBSERVER_HPP_

#include "skyway/core/connection_state.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

class ConnectionStateObserver {
public:
    virtual ~ConnectionStateObserver() = default;

    virtual void AddListener(core::ConnectionStateChangeNotifiable* listener)    = 0;
    virtual void RemoveListener(core::ConnectionStateChangeNotifiable* listener) = 0;
    virtual void OnConnectionStateChange(Transport* transport,
                                         const std::string& connection_state)    = 0;
    virtual void Dispose()                                                       = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_CONNECTION_STATE_OBSERVER_HPP_
