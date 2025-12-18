//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_INTERFACE_MEMBER_HPP_
#define SKYWAY_SIGNALING_INTERFACE_MEMBER_HPP_

#include <string>
#include <optional>

#include <json.hpp>

namespace skyway {
namespace signaling {
namespace interface {

struct Member {
    std::string id;
    std::optional<std::string> name;
    bool operator==(const Member& rhs) const { return id == rhs.id && name == rhs.name; }
    bool operator!=(const Member& rhs) const { return id != rhs.id || name != rhs.name; }
};

void from_json(const nlohmann::json& j, Member& member);
void to_json(nlohmann::json& j, const Member& member);

}  // namespace interface
}  // namespace signaling
}  // namespace skyway
#endif /* SKYWAY_SIGNALING_INTERFACE_MEMBER_HPP_ */
