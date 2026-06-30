//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_TYPES_HPP_
#define SKYWAY_MEDIA_TYPES_HPP_

/// @file types.hpp
/// @brief メディアに関する型を定義するヘッダーファイル

namespace skyway {
namespace media {

/// @brief オーディオバックエンドの種類
enum class AudioBackendType {
    /// @brief PulseAudioを使用します
    kPulseAudio,
    /// @brief オーディオバックエンドを使用しません
    kNone,
};

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_TYPES_HPP_ */
