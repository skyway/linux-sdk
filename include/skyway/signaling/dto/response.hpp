//
//  response.hpp
//  skyway
//
//  Created by ogura on 2023/09/15.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_DTO_RESPONSE_HPP_
#define SKYWAY_SIGNALING_DTO_RESPONSE_HPP_

#include <boost/optional.hpp>
#include <json.hpp>
#include <string>

namespace skyway {
namespace signaling {
namespace dto {

struct RequestResult {
    boost::optional<nlohmann::json> data;
    boost::optional<std::string> error_reason;
};

struct SendResult {
    bool is_success;
    boost::optional<std::string> error_reason;
};

}  // namespace dto
}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_DTO_RESPONSE_HPP_ */
