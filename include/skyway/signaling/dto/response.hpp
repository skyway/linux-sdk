//
//  response.hpp
//  skyway
//
//  Created by ogura on 2023/09/15.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
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
