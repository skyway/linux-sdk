//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_INTERFACE_SOCKET_HPP_
#define SKYWAY_SIGNALING_INTERFACE_SOCKET_HPP_

#include "skyway/signaling/client_event.hpp"

namespace skyway {
namespace signaling {
namespace interface {

class Socket {
public:
    class Listener {
    public:
        virtual void OnConnectionFailed()                       = 0;
        virtual void OnDataReceived(const nlohmann::json& data) = 0;
    };
    virtual ~Socket() = default;

    virtual void RegisterListener(Listener* listener) = 0;

    virtual bool Connect() = 0;

    virtual bool Send(const ClientEvent& event) = 0;

    virtual bool IsOpen() = 0;

    virtual void Dispose() = 0;
};

}  // namespace interface
}  // namespace signaling
}  // namespace skyway

#endif
