//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_HPP_
#define SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_HPP_

#include <json.hpp>

#include "skyway/core/chunk_messenger/dto/message.hpp"
#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/signaling/interface/member.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"
#include "skyway/signaling/interface/socket.hpp"

namespace skyway {
namespace core {
namespace interface {

class ChunkMessenger {
public:
    using WebSocketClientInterface  = network::interface::WebSocketClient;
    using SingnalingClientInterface = signaling::interface::SignalingClient;
    using SocketInterface           = signaling::interface::Socket;

    class Listener {
    public:
        virtual void OnMessage(const nlohmann::json& message) = 0;
    };
    virtual void ResetBlocking(const std::string& member_id)     = 0;
    virtual void InterruptBlocking(const std::string& member_id) = 0;
    virtual ~ChunkMessenger()                                    = default;

    virtual void AddListener(const signaling::interface::Member& remote_member,
                             Listener* listener) = 0;

    virtual void RemoveListener(const signaling::interface::Member& remote_member) = 0;

    virtual bool Connect(int connectivity_check_interval_sec) = 0;

    virtual chunk_messenger::dto::SendResult Send(const signaling::interface::Member& target_member,
                                                  const nlohmann::json& data,
                                                  const bool skip_response_wait = false) = 0;

    virtual void ResolveBufferedMessages(const signaling::interface::Member& sender) = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
