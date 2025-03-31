//
//  connection_state.hpp
//  skyway
//
//  Created by takemasa kaji on 2023/04/25.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_CONNECTION_STATE_HPP_
#define SKYWAY_CORE_CONNECTION_STATE_HPP_

#include <api/peer_connection_interface.h>

#include <string>

namespace skyway {
namespace core {

enum class ConnectionState { kNew, kConnecting, kConnected, kReconnecting, kDisconnected };

std::optional<ConnectionState> ConnectionStateFromPeerConnectionState(
    webrtc::PeerConnectionInterface::PeerConnectionState state);

std::optional<std::string> StringFromConnectionState(ConnectionState state);

class ConnectionStateChangeNotifiable {
public:
    /// @cond INTERNAL_SECTION
    virtual void OnConnectionStateChanged(const ConnectionState new_state) = 0;
    /// @endcond
};

}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CONNECTION_STATE_HPP */
