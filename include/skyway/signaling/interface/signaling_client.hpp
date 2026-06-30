//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_HPP_
#define SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_HPP_

#include <future>
#include <json.hpp>
#include <optional>
#include <string>
#include <unordered_map>

#include "skyway/signaling/dto/response.hpp"
#include "skyway/signaling/interface/member.hpp"
#include "skyway/signaling/interface/socket.hpp"

namespace skyway {
namespace signaling {
namespace interface {

class SignalingClient {
public:
    class Listener {
    public:
        virtual ~Listener() = default;
        virtual void OnConnectionFailed(){};

        virtual void OnRequestReceived(const nlohmann::json& data, const Member src) = 0;
        std::function<nlohmann::json(const nlohmann::json&, const std::string&, const std::string&)>
            reply;
    };

    class Delegator {
    public:
        virtual ~Delegator() = default;

        virtual nlohmann::json reply(const nlohmann::json& data,
                                     const std::string& src,
                                     const std::string& event_id) {
            return nlohmann::json::object();
        };
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

    virtual void InterruptBlocking(const std::string& member_id) = 0;

    virtual void ResetBlocking(const std::string& member_id) = 0;

    virtual void AddListener(Listener* listener) = 0;

    virtual void RemoveListener(Listener* listener) = 0;

    virtual bool Connect(Delegator* delegator, int connectivity_check_interval_sec) = 0;

    virtual signaling::dto::RequestResult Request(const Member& target,
                                                  const nlohmann::json& data,
                                                  const int timeout_sec,
                                                  const bool skip_response_wait = false) = 0;

    virtual signaling::dto::RequestResult Request(const Member& target,
                                                  const nlohmann::json& data,
                                                  const bool skip_response_wait = false) = 0;
};

}  // namespace interface
}  // namespace signaling
}  // namespace skyway

#endif
