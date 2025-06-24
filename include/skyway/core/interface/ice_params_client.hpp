//
//  ice_params_client.hpp
//  skyway
//
//  Created by salmon on 2023/05/16.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_ICE_PARAMS_CLIENT_HPP_
#define SKYWAY_CORE_INTERFACE_ICE_PARAMS_CLIENT_HPP_

namespace skyway {
namespace core {
namespace interface {

class IceParamsClient {
public:
    virtual ~IceParamsClient() = default;
    virtual webrtc::PeerConnectionInterface::IceServers FetchIceServers(
        const std::string& token,
        const std::string& channel_id,
        const std::string& member_id,
        std::optional<int> ttl) const = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_ICE_PARAMS_CLIENT_HPP_ */
