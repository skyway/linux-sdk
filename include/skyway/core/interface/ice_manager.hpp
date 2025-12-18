//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_ICE_MANAGER_HPP_
#define SKYWAY_CORE_INTERFACE_ICE_MANAGER_HPP_

namespace skyway {
namespace core {
namespace interface {

class IceManager {
public:
    virtual ~IceManager()                                                 = default;
    virtual webrtc::PeerConnectionInterface::IceServers FetchIceServers() = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_ICE_MANAGER_HPP_ */
