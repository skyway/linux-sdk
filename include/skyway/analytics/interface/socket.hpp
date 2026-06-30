//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ANALYTICS_INTERFACE_SOCKET_HPP_
#define SKYWAY_ANALYTICS_INTERFACE_SOCKET_HPP_

#include <json.hpp>

#include "skyway/analytics/client_event.hpp"
#include "skyway/analytics/server_event.hpp"

namespace skyway {
namespace analytics {
namespace interface {

class Socket {
public:
    class Listener {
    public:
        virtual void OnConnectionFailed()               = 0;
        virtual void OnOpen(const OpenPayload& payload) = 0;
    };
    virtual ~Socket() = default;

    virtual void RegisterListener(Listener* listener) = 0;

    virtual bool Connect() = 0;

    virtual bool Send(const ClientEvent& event) = 0;

    virtual bool IsOpen() const = 0;

    virtual void Dispose() = 0;
};

}  // namespace interface
}  // namespace analytics
}  // namespace skyway

#endif
