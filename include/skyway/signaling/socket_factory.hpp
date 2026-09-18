//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_SOCKET_FACTORY_HPP_
#define SKYWAY_SIGNALING_SOCKET_FACTORY_HPP_

#include <memory>
#include <optional>
#include <string>

#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/platform/interface/platform_info_delegator.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"
#include "skyway/signaling/interface/socket.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {

namespace signaling {

class SocketFactory {
public:
    std::unique_ptr<interface::Socket> Create(
        const std::string& channel_id,
        const std::optional<std::string> channel_name,
        const std::string& member_id,
        const std::optional<std::string> member_name,
        std::weak_ptr<token::interface::AuthTokenManager> auth,
        std::shared_ptr<network::interface::WebSocketClient> ws,
        const platform::interface::PlatformInfoDelegator* platform_info,
        const interface::SignalingClient::Options& options);

private:
    std::string GetSignalingServerSessionEndpoint(const std::string& signaling_domain,
                                                  bool use_secure_protocol);
};

}  // namespace signaling
}  // namespace skyway

#endif
