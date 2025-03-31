//
//  domain.hpp
//  skyway
//
//  Created by sandabu on 2021/12/21.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_MODEL_DOMAIN_HPP_
#define SKYWAY_MODEL_DOMAIN_HPP_

#include <optional>
#include <json.hpp>

namespace skyway {
namespace model {

enum class Side { kLocal, kRemote };
enum class MemberType { kPerson, kBot };
enum class ContentType { kAudio, kVideo, kData };

std::string ToString(Side side);
std::string ToString(MemberType type);
std::string ToString(ContentType type);

std::optional<Side> ToSide(const std::string& side);
std::optional<MemberType> ToMemberType(const std::string& type);
std::optional<ContentType> ToContentType(const std::string& type);

/// @brief コーデック情報
struct Codec {
    /// @brief Dtxオプションを適応するかのオプション
    struct Parameters {
        std::optional<bool> use_dtx;
    };
    /// @brief mimetype
    std::string mime_type;
    /// @brief パラメーター
    Parameters parameters;
};

/// @brief エンコーディング設定
struct Encoding {
    /// @brief Id
    std::optional<std::string> id;
    /// @brief 最大ビットレート
    std::optional<int> max_bitrate;
    /// @brief 解像度の倍率
    std::optional<double> scale_resolution_down_by;
    /// @brief 最大フレームレート
    std::optional<double> max_framerate;
};
/// @brief メンバー情報
struct Member {
    /// @brief `Join`時に使用するメンバー情報
    struct Init {
        /// @brief 種類
        MemberType type;
        /// @brief サブタイプ
        std::string subtype;
        /// @brief 名前
        std::optional<std::string> name;
        /// @brief Metadata
        std::optional<std::string> metadata;
        /// @brief 生存確認の間隔
        std::optional<int> keepalive_interval_sec;
        /// @brief 生存確認の間隔を超えてChannelからMemberが削除されるまでの時間
        std::optional<int> keepalive_interval_gap_sec;
    };
    /// @brief Id
    std::string id;
    /// @brief 名前
    std::optional<std::string> name;
    /// @brief 種類
    MemberType type;
    /// @brief サブタイプ
    std::string subtype;
    /// @brief Metadata
    std::optional<std::string> metadata;
    // the `name` can be retrieved from `init` but set the value returned by server.
    Member() {}
    Member(const std::string& id, const std::optional<std::string>& name, const Init& init) {
        this->id   = id;
        this->name = name;
        type       = init.type;
        subtype    = init.subtype;
        metadata   = init.metadata;
    }
};

/// @brief Publication情報
struct Publication {
    struct Init {
        std::string channel_id;
        std::string publisher_id;
        ContentType content_type;
        std::optional<std::string> origin;
        std::optional<std::string> metadata;
        std::vector<Codec> codec_capabilities = {};
        std::vector<Encoding> encodings       = {};
        bool is_enabled;
    };
    /// @brief Id
    std::string id;
    /// @brief PublishしたメンバーのId
    std::string publisher_id;
    /// @brief Origin
    std::optional<std::string> origin;
    /// @brief コンテンツの種類
    ContentType content_type;
    /// @brief Metadata
    std::optional<std::string> metadata;
    /// @brief コーデック一覧
    std::vector<Codec> codec_capabilities;
    /// @brief エンコーディング一覧
    std::vector<Encoding> encodings;
    /// @brief 有効か無効か
    bool is_enabled;
    Publication() {}
    Publication(const std::string& id, const Init& init) {
        this->id           = id;
        publisher_id       = init.publisher_id;
        origin             = init.origin;
        content_type       = init.content_type;
        metadata           = init.metadata;
        codec_capabilities = init.codec_capabilities;
        encodings          = init.encodings;
        is_enabled         = init.is_enabled;
    }
};

/// @brief Subscription情報
struct Subscription {
    struct Init {
        std::string channel_id;
        std::string publication_id;
        std::string subscriber_id;
        bool is_enabled;
    };
    /// @brief Id
    std::string id;
    /// @brief このSubscriptionに紐づくPublicationのId
    std::string publication_id;
    /// @brief このSubscriptionをSubscribeしているメンバーのId
    std::string subscriber_id;
    /// @brief 有効か無効か
    bool is_enabled;
    Subscription() {}
    Subscription(const std::string& id, const Init& init) {
        this->id       = id;
        publication_id = init.publication_id;
        subscriber_id  = init.subscriber_id;
        is_enabled     = init.is_enabled;
    }
};

/// @brief Channel情報
struct Channel {
    /// @brief `Create`もしくは`FindOrCreate`で指定する情報
    struct Init {
        /// @brief Channelの名前
        std::optional<std::string> name;
        /// @brief ChannelのMetadata
        std::optional<std::string> metadata;
    };
    /// @brief `Find`もしくは`FindOrCreate`で指定する情報
    struct Query {
        /// @brief Channelの名前
        std::optional<std::string> name;
        /// @brief ChannelのId
        std::optional<std::string> id;
    };
    /// @brief Id
    std::string id;
    /// @brief 名前
    std::optional<std::string> name;
    /// @brief Metadata
    std::optional<std::string> metadata;
    /// @brief このChannelの存在するメンバーの一覧
    std::vector<Member> members;
    /// @brief このChannelの存在するPublicationの一覧
    std::vector<Publication> publications;
    /// @brief このChannelの存在するSubscriptionの一覧
    std::vector<Subscription> subscriptions;
    /// @brief バージョン
    uint64_t version;
};

/// @deprecated 本機能は非推奨です。
/// @brief 統計情報の詳細
struct [[deprecated]] WebRTCStatsReport {
    /// @brief Id
    std::string id;
    /// @brief 種類
    std::string type;
    /// @brief 各パラメーターに対応するJson
    std::unordered_map<std::string, nlohmann::json> params;
};

/// @deprecated 本機能は非推奨です。
/// @brief 統計情報
struct [[deprecated]] WebRTCStats {
    /// @brief 統計情報の一覧
    std::vector<WebRTCStatsReport> reports;
};

void from_json(const nlohmann::json& j, Codec& codec);
void from_json(const nlohmann::json& j, Encoding& encoding);
void from_json(const nlohmann::json& j, Channel& channel);
void from_json(const nlohmann::json& j, Member& member);
void from_json(const nlohmann::json& j, Publication& publication);
void from_json(const nlohmann::json& j, Subscription& subscription);
/// @deprecated 本機能は非推奨な機能であるSubscriptionStatsReportPayloadを利用しています。
[[deprecated]] void from_json(const nlohmann::json& j, WebRTCStats& stats);

void to_json(nlohmann::json& j, const Codec& codec);
void to_json(nlohmann::json& j, const Encoding& encoding);

}  // namespace model
}  // namespace skyway

#endif /* SKYWAY_MODEL_DOMAIN_HPP_ */
