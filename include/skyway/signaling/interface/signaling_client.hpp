//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_HPP_
#define SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_HPP_

#include <future>
#include <json.hpp>
#include <optional>
#include <string>

#include "skyway/signaling/dto/response.hpp"
#include "skyway/signaling/interface/member.hpp"

namespace skyway {
namespace signaling {
namespace interface {

class SignalingClient {
public:
    class Listener {
    public:
        virtual ~Listener()                                   = default;
        virtual void OnMessage(const nlohmann::json& message) = 0;
    };

    struct Options {
        std::optional<int> connectivity_check_interval_sec;
        std::optional<std::string> signaling_domain;
        std::optional<bool> use_secure_protocol;
        bool operator==(const Options& rhs) const {
            if (connectivity_check_interval_sec == rhs.connectivity_check_interval_sec &&
                signaling_domain == rhs.signaling_domain &&
                use_secure_protocol == rhs.use_secure_protocol) {
                return true;
            }
            return false;
        }
    };
    virtual ~SignalingClient() = default;

    virtual void Dispose() = 0;

    virtual void InterruptBlocking(const std::string& member_id) = 0;

    virtual void ResetBlocking(const std::string& member_id) = 0;

    virtual void AddListener(const Member& remote_member, Listener* listener) = 0;

    virtual void RemoveListener(const Member& remote_member) = 0;

    virtual bool Connect(int connectivity_check_interval_sec) = 0;

    virtual std::future<dto::SendResult> Send(const Member& target,
                                              const nlohmann::json& data,
                                              bool skip_response_wait = false) = 0;

    virtual void ResolveBufferedMessages(const Member& sender) = 0;
};

}  // namespace interface
}  // namespace signaling
}  // namespace skyway

#endif
