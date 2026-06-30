//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_DOMAIN_HPP_
#define SKYWAY_DOMAIN_HPP_

#include <string>

/// @file domain.hpp
/// @brief SkyWay全体で使用される列挙型や定数を定義するヘッダーファイル

namespace skyway {
namespace domain {

/// @brief Streamの所在(LocalかRemoteか)
enum class Side { kLocal, kRemote };

/// @brief Memberの種別
enum class MemberType { kPerson, kBot };

/// @brief Publicationの通信方式
enum class PublicationType { kP2P, kSFU };

/// @brief コンテンツの種類
enum class ContentType { kAudio, kVideo, kData };

/// @brief ログレベル
enum class LogLevel { kOff, kTrace, kDebug, kInfo, kWarn, kError };

/// @brief TURNサーバーの利用ポリシー
enum class TurnPolicy {
    kEnable,
    kDisable,
    kTurnOnly,
};

inline std::string ToString(Side side) {
    switch (side) {
        case Side::kLocal:
            return "local";
        case Side::kRemote:
            return "remote";
    }
    return "";
}

inline std::string ToString(PublicationType type) {
    switch (type) {
        case PublicationType::kP2P:
            return "p2p";
        case PublicationType::kSFU:
            return "sfu";
    }
    return "";
}

inline std::string ToString(ContentType type) {
    switch (type) {
        case ContentType::kAudio:
            return "Audio";
        case ContentType::kVideo:
            return "Video";
        case ContentType::kData:
            return "Data";
    }
    return "";
}

}  // namespace domain
}  // namespace skyway

#endif /* SKYWAY_DOMAIN_HPP_ */
