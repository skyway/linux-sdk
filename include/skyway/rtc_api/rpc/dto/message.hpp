//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_RPC_DTO_MESSAGE_HPP_
#define SKYWAY_RTC_API_RPC_DTO_MESSAGE_HPP_

#include <optional>

#include <json.hpp>

namespace skyway {
namespace rtc_api {
namespace rpc {
namespace dto {

struct RequestMessage {
    std::string json_rpc;
    std::string method;
    nlohmann::json params;
    std::optional<std::string> id;
    bool operator==(const RequestMessage& rhs) const { return id == rhs.id; }
    struct Hash {
        std::size_t operator()(const RequestMessage& message) const {
            std::string id = message.id == std::nullopt ? "" : message.id.value();
            return std::hash<std::string>()(id);
        }
    };
};

struct ResponseMessage {
    std::string json_rpc;
    nlohmann::json result;
    std::string id;
};

struct ResponseErrorMessage {
    struct Error {
        int code;
        std::string message;
    };
    std::string json_rpc;
    Error error;
    std::string id;
};

void from_json(const nlohmann::json& j, RequestMessage& message);
void from_json(const nlohmann::json& j, ResponseMessage& message);
void from_json(const nlohmann::json& j, ResponseErrorMessage& error);

void to_json(nlohmann::json& j, const RequestMessage& message);
void to_json(nlohmann::json& j, const ResponseMessage& message);
void to_json(nlohmann::json& j, const ResponseErrorMessage& message);

}  // namespace dto
}  // namespace rpc
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_RPC_DTO_MESSAGE_HPP_ */
