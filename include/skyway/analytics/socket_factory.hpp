//
//  socket_factory.hpp
//  skyway
//
//  Created by Muranaka Kei on 2023/11/24.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ANALYTICS_SOCKET_FACTORY_HPP_
#define SKYWAY_ANALYTICS_SOCKET_FACTORY_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/analytics/interface/socket.hpp"
#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/platform/interface/platform_info_delegator.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace analytics {

class SocketFactory {
public:
    static std::unique_ptr<interface::Socket> Create(
        const std::string& channel_id,
        const std::optional<std::string>& channel_name,
        const std::string& member_id,
        const std::optional<std::string>& member_name,
        const std::weak_ptr<token::interface::AuthTokenManager> auth,
        const std::shared_ptr<network::interface::WebSocketClient>& ws,
        const platform::interface::PlatformInfoDelegator* platform_info,
        const interface::AnalyticsClient::Options& options);

private:
    static std::string GetAnalyticsServerSessionEndpoint(const std::string& analytics_domain,
                                                         bool use_secure_protocol);
};

}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_SOCKET_FACTORY_HPP_ */
