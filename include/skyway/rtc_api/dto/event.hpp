//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_DTO_EVENT_HPP_
#define SKYWAY_RTC_API_DTO_EVENT_HPP_

#include <json.hpp>

#include "skyway/model/domain.hpp"

namespace skyway {
namespace rtc_api {
namespace dto {

struct ChannelSummary {
    std::string id;
    uint64_t version;
    std::optional<std::string> metadata;
};

struct EventData {
    ChannelSummary channel;
};

struct ChannelMetadataUpdatedEventData : public EventData {};

struct MemberAddedEventData : public EventData {
    model::Member member;
};

struct MemberRemovedEventData : public EventData {
    model::Member member;
};

struct MemberMetadataUpdatedEventData : public EventData {
    model::Member member;
};

struct StreamPublishedEventData : public EventData {
    model::Publication publication;
};

struct StreamUnpublishedEventData : public EventData {
    model::Publication publication;
};

struct PublicationEnabledEventData : public EventData {
    model::Publication publication;
};

struct PublicationDisabledEventData : public EventData {
    model::Publication publication;
};

struct PublicationMetadataUpdatedEventData : public EventData {
    model::Publication publication;
};

struct StreamSubscribedEventData : public EventData {
    model::Publication publication;
    model::Subscription subscription;
};

struct StreamUnsubscribedEventData : public EventData {
    model::Subscription subscription;
};

void from_json(const nlohmann::json& j, ChannelSummary& summary);
void from_json(const nlohmann::json& j, EventData& data);
void from_json(const nlohmann::json& j, ChannelMetadataUpdatedEventData& data);
void from_json(const nlohmann::json& j, MemberAddedEventData& data);
void from_json(const nlohmann::json& j, MemberRemovedEventData& data);
void from_json(const nlohmann::json& j, MemberMetadataUpdatedEventData& data);
void from_json(const nlohmann::json& j, StreamPublishedEventData& data);
void from_json(const nlohmann::json& j, StreamUnpublishedEventData& data);
void from_json(const nlohmann::json& j, PublicationEnabledEventData& data);
void from_json(const nlohmann::json& j, PublicationDisabledEventData& data);
void from_json(const nlohmann::json& j, PublicationMetadataUpdatedEventData& data);
void from_json(const nlohmann::json& j, StreamSubscribedEventData& data);
void from_json(const nlohmann::json& j, StreamUnsubscribedEventData& data);

}  // namespace dto
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_DTO_EVENT_HPP_ */
