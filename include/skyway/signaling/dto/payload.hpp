//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_DTO_PAYLOAD_HPP_
#define SKYWAY_SIGNALING_DTO_PAYLOAD_HPP_

#include <json.hpp>

#include "skyway/signaling/interface/member.hpp"

namespace skyway {
namespace signaling {
namespace dto {

namespace incoming {

struct Message {
    interface::Member src;
    nlohmann::json data;
};

struct Request : Message {
    std::string request_event_id;
};

struct Response : Message {
    std::string request_event_id;
};

struct EventAccepted {
    std::string event_id;
};

struct EventRejected {
    std::string event_id;
    std::string reason;
};

void from_json(const nlohmann::json& j, Request& payload);
void from_json(const nlohmann::json& j, Response& payload);
void from_json(const nlohmann::json& j, EventAccepted& payload);
void from_json(const nlohmann::json& j, EventRejected& payload);

}  // namespace incoming

namespace outgoing {

struct Request {
    const interface::Member dst;
    const nlohmann::json data;
    Request(const interface::Member& dst, const nlohmann::json& data) : dst(dst), data(data) {}
};

struct Response {
    const interface::Member dst;
    std::string request_event_id;
    const nlohmann::json data;
    Response(const interface::Member& dst,
             const std::string& request_event_id,
             const nlohmann::json& data)
        : dst(dst), request_event_id(request_event_id), data(data) {}
};

void to_json(nlohmann::json& j, const Request& payload);
void to_json(nlohmann::json& j, const Response& payload);

}  // namespace outgoing
}  // namespace dto
}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_DTO_PAYLOAD_HPP_ */
