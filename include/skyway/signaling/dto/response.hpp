//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_DTO_RESPONSE_HPP_
#define SKYWAY_SIGNALING_DTO_RESPONSE_HPP_

#include <string>
#include <optional>

#include <json.hpp>

namespace skyway {
namespace signaling {
namespace dto {

struct RequestResult {
    std::optional<nlohmann::json> data;
    std::optional<std::string> error_reason;
};

struct SendResult {
    bool is_success;
    std::optional<std::string> error_reason;
};

}  // namespace dto
}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_DTO_RESPONSE_HPP_ */
