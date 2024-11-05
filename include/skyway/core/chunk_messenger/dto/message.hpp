//
//  message.hpp
//  skyway
//
//  Created by sandabu on 2021/11/11.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_CHUNK_MESSENGER_DTO_MESSAGE_HPP_
#define SKYWAY_CORE_CHUNK_MESSENGER_DTO_MESSAGE_HPP_

#include <boost/optional.hpp>
#include <json.hpp>
#include <string>

namespace skyway {
namespace core {
namespace chunk_messenger {
namespace dto {

struct ChunkedMessage {
    std::string type;
    unsigned int length;
    unsigned int offset;
    std::string chunk;
    std::string id;
};

struct SendResult {
    bool is_success;
    boost::optional<std::string> error_reason;
};

void from_json(const nlohmann::json& j, ChunkedMessage& message);
void to_json(nlohmann::json& j, const ChunkedMessage& message);

}  // namespace dto
}  // namespace chunk_messenger
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CHUNK_MESSENGER_DTO_MESSAGE_HPP_ */
