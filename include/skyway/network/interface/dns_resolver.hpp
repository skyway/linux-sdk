//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_DNS_RESOLVER_HPP
#define SKYWAY_NETWORK_INTERFACE_DNS_RESOLVER_HPP

#include <boost/asio.hpp>

namespace skyway {
namespace network {
namespace interface {

template <typename InternetProtocol>
class DnsResolver {
public:
    virtual ~DnsResolver() = default;
    virtual boost::asio::ip::basic_resolver_results<InternetProtocol> Resolve(
        const std::string& host, const std::string& port) = 0;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif /* SKYWAY_NETWORK_INTERFACE_DNS_RESOLVER_HPP */
