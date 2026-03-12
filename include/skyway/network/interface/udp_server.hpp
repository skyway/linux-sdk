//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_UDP_SERVER_HPP
#define SKYWAY_NETWORK_INTERFACE_UDP_SERVER_HPP

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <boost/asio.hpp>

namespace skyway {
namespace network {
namespace interface {

class UdpServer {
public:
    class PacketHandler {
    public:
        virtual ~PacketHandler()                                        = default;
        virtual void OnPacketReceived(const uint8_t* data, size_t size) = 0;
    };

    virtual ~UdpServer() = default;

    virtual bool Start(const std::string& local_address, uint16_t local_port) = 0;

    virtual void Stop() = 0;

    virtual void RegisterPacketHandler(PacketHandler* handler) = 0;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif  // SKYWAY_NETWORK_INTERFACE_UDP_SERVER_HPP
