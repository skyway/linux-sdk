//
//  ice_manager.hpp
//  skyway
//
//  Created by salmon on 2023/04/24.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_ICE_ICE_MANAGER_HPP_
#define SKYWAY_CORE_ICE_ICE_MANAGER_HPP_

#include <api/peer_connection_interface.h>

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/ice_manager.hpp"
#include "skyway/core/interface/ice_params_client.hpp"

namespace skyway {
namespace core {
namespace ice {
class IceManager : public interface::IceManager {
public:
    IceManager(interface::Channel* channel);
    IceManager(token::interface::AuthTokenManager* auth,
               interface::Channel* channel,
               std::unique_ptr<interface::IceParamsClient> ice_client);

    webrtc::PeerConnectionInterface::IceServers FetchIceServers() override;

private:
    std::unique_ptr<interface::IceParamsClient> ice_client_;
    token::interface::AuthTokenManager* auth_;
    interface::Channel* channel_;
};

}  // namespace ice
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_ICE_ICE_MANAGER_HPP_ */
