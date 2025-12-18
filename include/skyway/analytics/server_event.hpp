//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ANALYTICS_SERVER_EVENT_HPP_
#define SKYWAY_ANALYTICS_SERVER_EVENT_HPP_

#include <chrono>
#include <json.hpp>
#include <optional>
#include <string>

#include "skyway/model/domain.hpp"

namespace skyway {
namespace analytics {

struct OpenPayload;
struct AcknowledgePayload;

class ServerEvent {
public:
    static std::optional<ServerEvent> Parse(const std::string& json_string);

    bool IsOpenEvent() const;
    bool IsAcknowledgeEvent() const;

    std::optional<OpenPayload> GetOpenPayload() const;
    std::optional<AcknowledgePayload> GetAcknowledgePayload() const;

private:
    static const std::string kOpen;
    static const std::string kAcknowledge;

    ServerEvent() = default;

    std::string id_;
    std::string type_;
    nlohmann::json::object_t payload_;

public:
    friend class nlohmann::adl_serializer<ServerEvent>;
};

struct OpenPayload {
    struct StatsRequest {
        struct Type {
            struct Property {
                bool normalization;
                std::string output_key;
                std::vector<model::ContentType> content_types;
            };

            std::string type;
            std::unordered_map<std::string, Property> properties;
        };

        std::chrono::seconds interval_sec;
        std::vector<Type> types;
    };

    StatsRequest stats_request;
};

struct AcknowledgePayload {
    bool IsInvalidPayload() const;
    bool IsUnexpected() const;

    std::string
        event_id;  // Defined as Optional, but has actual value when the client set events' id.
    bool ok;
    std::optional<std::string> reason;

private:
    static const std::string kInvalidPayload;
    static const std::string kUnexpected;
};

void from_json(const nlohmann::json& j, OpenPayload& payload);
void from_json(const nlohmann::json& j, OpenPayload::StatsRequest& request);
void from_json(const nlohmann::json& j, OpenPayload::StatsRequest::Type& type);
void from_json(const nlohmann::json& j, OpenPayload::StatsRequest::Type::Property& property);
void from_json(const nlohmann::json& j, AcknowledgePayload& payload);

}  // namespace analytics
}  // namespace skyway

namespace nlohmann {

template <>
struct adl_serializer<skyway::analytics::ServerEvent> {
    static skyway::analytics::ServerEvent from_json(const json& j) {
        skyway::analytics::ServerEvent event;
        j.at("id").get_to(event.id_);
        j.at("type").get_to(event.type_);
        j.at("payload").get_to(event.payload_);
        return event;
    }
};

}  // namespace nlohmann

#endif /* SKYWAY_ANALYTICS_SERVER_EVENT_HPP_ */
