//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MODEL_DOMAIN_HPP_
#define SKYWAY_MODEL_DOMAIN_HPP_

#include <json.hpp>
#include <optional>

namespace skyway {
namespace model {

enum class Side { kLocal, kRemote };
enum class MemberType { kPerson, kBot };
enum class PublicationType { kP2P, kSFU };
enum class ContentType { kAudio, kVideo, kData };

std::string ToString(Side side);
std::string ToString(MemberType type);
std::string ToString(PublicationType type);
std::string ToString(ContentType type);

std::optional<Side> ToSide(const std::string& side);
std::optional<MemberType> ToMemberType(const std::string& type);
std::optional<PublicationType> ToPublicationType(const std::string& type);
std::optional<ContentType> ToContentType(const std::string& type);

struct Codec {
    struct Parameters {
        std::optional<bool> use_dtx;
    };

    std::string mime_type;

    Parameters parameters;
};

struct Encoding {
    std::optional<std::string> id;

    std::optional<int> max_bitrate;

    std::optional<double> scale_resolution_down_by;

    std::optional<double> max_framerate;
};

struct Member {
    struct Init {
        MemberType type;

        std::string subtype;

        std::optional<std::string> name;

        std::optional<std::string> metadata;

        std::optional<int> keepalive_interval_sec;

        std::optional<int> keepalive_interval_gap_sec;
    };

    std::string id;

    std::optional<std::string> name;

    MemberType type;

    std::string subtype;

    std::optional<std::string> metadata;

    Member() {}
    Member(const std::string& id, const std::optional<std::string>& name, const Init& init) {
        this->id   = id;
        this->name = name;
        type       = init.type;
        subtype    = init.subtype;
        metadata   = init.metadata;
    }
};

struct Publication {
    struct Init {
        std::string channel_id;
        std::string publisher_id;
        PublicationType type;
        ContentType content_type;
        std::optional<std::string> origin;
        std::optional<std::string> metadata;
        std::vector<Codec> codec_capabilities = {};
        std::vector<Encoding> encodings       = {};
        bool is_enabled;
    };

    std::string id;

    std::string publisher_id;

    std::optional<std::string> origin;
    PublicationType type;

    ContentType content_type;

    std::optional<std::string> metadata;

    std::vector<Codec> codec_capabilities;

    std::vector<Encoding> encodings;

    bool is_enabled;
    Publication() {}
    Publication(const std::string& id, const Init& init) {
        this->id           = id;
        publisher_id       = init.publisher_id;
        origin             = init.origin;
        type               = init.type;
        content_type       = init.content_type;
        metadata           = init.metadata;
        codec_capabilities = init.codec_capabilities;
        encodings          = init.encodings;
        is_enabled         = init.is_enabled;
    }
};

struct Subscription {
    struct Init {
        std::string channel_id;
        std::string publication_id;
        std::string subscriber_id;
        bool is_enabled;
    };

    std::string id;

    std::string publication_id;

    std::string subscriber_id;

    bool is_enabled;
    Subscription() {}
    Subscription(const std::string& id, const Init& init) {
        this->id       = id;
        publication_id = init.publication_id;
        subscriber_id  = init.subscriber_id;
        is_enabled     = init.is_enabled;
    }
};

struct Channel {
    struct Init {
        std::optional<std::string> name;

        std::optional<std::string> metadata;
    };

    struct Query {
        std::optional<std::string> name;

        std::optional<std::string> id;
    };

    std::string id;

    std::optional<std::string> name;

    std::optional<std::string> metadata;

    std::vector<Member> members;

    std::vector<Publication> publications;

    std::vector<Subscription> subscriptions;

    uint64_t version;
};

struct [[deprecated]] WebRTCStatsReport {
    std::string id;

    std::string type;

    std::unordered_map<std::string, nlohmann::json> params;
};

struct [[deprecated]] WebRTCStats {
    std::vector<WebRTCStatsReport> reports;
};

void from_json(const nlohmann::json& j, Codec& codec);
void from_json(const nlohmann::json& j, Encoding& encoding);
void from_json(const nlohmann::json& j, Channel& channel);
void from_json(const nlohmann::json& j, Member& member);
void from_json(const nlohmann::json& j, Publication& publication);
void from_json(const nlohmann::json& j, Subscription& subscription);

[[deprecated]] void from_json(const nlohmann::json& j, WebRTCStats& stats);

void to_json(nlohmann::json& j, const Codec& codec);
void to_json(nlohmann::json& j, const Encoding& encoding);

}  // namespace model
}  // namespace skyway

#endif
