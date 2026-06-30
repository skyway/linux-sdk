//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_CLIENT_EVENT_HPP_
#define SKYWAY_SIGNALING_CLIENT_EVENT_HPP_

#include <future>
#include <json.hpp>
#include <string>

namespace skyway {
namespace signaling {

struct ClientEvent {
    ClientEvent(const std::string& name, const nlohmann::json& payload);
    ClientEvent(const std::string& name);

    bool ValidateJsonSize() const;

    std::string name;
    std::string id;
    nlohmann::json payload;
};

void to_json(nlohmann::json& j, const ClientEvent& event);

}  // namespace signaling
}  // namespace skyway

#endif
