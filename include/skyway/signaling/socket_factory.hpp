//
//  socket_factory.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2022/10/07.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_SOCKET_FACTORY_HPP_
#define SKYWAY_SIGNALING_SOCKET_FACTORY_HPP_

#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/platform/interface/platform_info_delegator.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"
#include "skyway/signaling/interface/socket.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace signaling {

class SocketFactory {
public:
    using SignalingClinetInterface       = interface::SignalingClient;
    using SocketInterface                = interface::Socket;
    using WebSocketClientInterface       = network::interface::WebSocketClient;
    using PlatformInfoDelegatorInterface = platform::interface::PlatformInfoDelegator;
    std::unique_ptr<SocketInterface> Create(const std::string& channel_id,
                                            const std::optional<std::string> channel_name,
                                            const std::string& member_id,
                                            const std::optional<std::string> member_name,
                                            std::weak_ptr<token::interface::AuthTokenManager> auth,
                                            std::shared_ptr<WebSocketClientInterface> ws,
                                            const PlatformInfoDelegatorInterface* platform_info,
                                            const SignalingClinetInterface::Options& options);

private:
    std::string GetSignalingServerSessionEndpoint(const std::string& signaling_domain,
                                                  bool use_secure_protocol);
};

}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_SOCKET_FACTORY_HPP_ */
