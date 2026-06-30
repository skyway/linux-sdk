//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_TYPES_HPP_
#define SKYWAY_ROOM_TYPES_HPP_

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <json.hpp>

/// @file types.hpp
/// @brief Roomの状態や種別、統計情報などの型を定義するヘッダーファイル

namespace skyway {
namespace room {

/// @brief Roomの種別
enum class RoomType { kDefault, kP2P, kSFU };

/// @brief Roomの状態
enum class RoomState { kOpened, kClosed };

/// @brief Memberの入室状態
enum class MemberState { kJoined, kLeft };

/// @brief Publication/Subscriptionの接続状態
enum class ConnectionState { kNew, kConnecting, kConnected, kReconnecting, kDisconnected };

/// @brief Publicationの公開状態
enum class PublicationState { kEnabled, kDisabled, kCanceled };

/// @brief Subscriptionの購読状態
enum class SubscriptionState { kEnabled, kDisabled, kCanceled };

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

/// @brief ConnectionStateを文字列に変換する
inline std::string ToString(ConnectionState state) {
    switch (state) {
        case ConnectionState::kNew:
            return "new";
        case ConnectionState::kConnecting:
            return "connecting";
        case ConnectionState::kConnected:
            return "connected";
        case ConnectionState::kReconnecting:
            return "reconnecting";
        case ConnectionState::kDisconnected:
            return "disconnected";
    }
    return "";
}

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_TYPES_HPP_ */
