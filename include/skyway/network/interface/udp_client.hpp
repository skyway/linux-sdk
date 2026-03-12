//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_UDP_CLIENT_HPP
#define SKYWAY_NETWORK_INTERFACE_UDP_CLIENT_HPP

#include <cstdint>
#include <functional>

namespace skyway {
namespace network {
namespace interface {

class UdpClient {
public:
    virtual ~UdpClient() = default;

    virtual bool Open() = 0;

    virtual bool Send(const uint8_t* data, size_t size) = 0;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif  // SKYWAY_NETWORK_INTERFACE_UDP_CLIENT_HPP
