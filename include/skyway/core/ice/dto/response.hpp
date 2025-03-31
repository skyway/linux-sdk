//
//  response.hpp
//  skyway
//
//  Created by sandabu on 2022/02/15.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_ICE_DTO_RESPONSE_HPP_
#define SKYWAY_CORE_ICE_DTO_RESPONSE_HPP_

#include <string>
#include <optional>

#include <json.hpp>

namespace skyway {
namespace core {
namespace ice {
namespace dto {

struct Stun {
    std::string domain;
    int port;
};

struct Turn {
    std::string username;
    std::string credential;
    std::string domain;
    int port;
};

struct IceParamsResponse {
    Stun stun;
    std::optional<Turn> turn;
};

void from_json(const nlohmann::json& j, Stun& stun);
void from_json(const nlohmann::json& j, Turn& turn);
void from_json(const nlohmann::json& j, IceParamsResponse& response);

}  // namespace dto
}  // namespace ice
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_ICE_DTO_RESPONSE_HPP_ */
