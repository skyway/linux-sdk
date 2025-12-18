//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_RPC_DTO_RESULT_HPP_
#define SKYWAY_RTC_API_RPC_DTO_RESULT_HPP_

#include <optional>

#include <json.hpp>

#include "skyway/model/domain.hpp"

namespace skyway {
namespace rtc_api {
namespace rpc {
namespace dto {

struct CreateChannelResult {
    struct Channel {
        std::string id;
        uint64_t version;
    };
    Channel channel;
};

struct FindOrCreateChannelResult {
    model::Channel channel;
};

struct GetChannelResult {
    model::Channel channel;
};

struct GetChannelByNameResult {
    model::Channel channel;
};

struct DeleteChannelResult {
    uint64_t version;
};

struct UpdateChannelMetadataResult {
    uint64_t version;
};

struct JoinChannelResult {
    std::string member_id;
    std::optional<std::string> member_name;
    uint64_t version;
};

struct LeaveChannelResult {
    uint64_t version;
};

struct UpdateMemberMetadataResult {
    uint64_t version;
};

struct UpdateMemberTtlResult {
    // Empty
};

struct GetServerUnixTimeResult {
    time_t unix_time = 0;
};

struct UpdateAuthTokenResult {
    // Empty
};

struct PublishStreamResult {
    std::string id;
    uint64_t version;
};

struct UpdatePublicationMetadataResult {
    uint64_t version;
};

struct UnpublishStreamResult {
    uint64_t version;
};

struct EnablePublicationResult {
    uint64_t version;
};

struct DisablePublicationResult {
    uint64_t version;
};

struct SubscribeStreamResult {
    std::string subscription_id;
    uint64_t version;
};

struct UnsubscribeStreamResult {
    uint64_t version;
};

struct SubscribeChannelEventsResult {};

struct ListChannelEventResult {};

void from_json(const nlohmann::json& j, CreateChannelResult& result);
void from_json(const nlohmann::json& j, FindOrCreateChannelResult& result);
void from_json(const nlohmann::json& j, GetChannelResult& result);
void from_json(const nlohmann::json& j, GetChannelByNameResult& result);
void from_json(const nlohmann::json& j, DeleteChannelResult& result);
void from_json(const nlohmann::json& j, UpdateChannelMetadataResult& result);
void from_json(const nlohmann::json& j, JoinChannelResult& result);
void from_json(const nlohmann::json& j, LeaveChannelResult& result);
void from_json(const nlohmann::json& j, UpdateMemberMetadataResult& result);
void from_json(const nlohmann::json& j, GetServerUnixTimeResult& result);
void from_json(const nlohmann::json& j, UpdateMemberTtlResult& result);
void from_json(const nlohmann::json& j, UpdateAuthTokenResult& result);
void from_json(const nlohmann::json& j, PublishStreamResult& result);
void from_json(const nlohmann::json& j, UpdatePublicationMetadataResult& result);
void from_json(const nlohmann::json& j, UnpublishStreamResult& result);
void from_json(const nlohmann::json& j, EnablePublicationResult& result);
void from_json(const nlohmann::json& j, DisablePublicationResult& result);
void from_json(const nlohmann::json& j, SubscribeStreamResult& result);
void from_json(const nlohmann::json& j, UnsubscribeStreamResult& result);
void from_json(const nlohmann::json& j, SubscribeChannelEventsResult& result);
void from_json(const nlohmann::json& j, ListChannelEventResult& result);

}  // namespace dto
}  // namespace rpc
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_RPC_DTO_RESULT_HPP_ */
