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

/// @brief 音声処理に関する設定
struct AudioProcessingOptions {
    /// @brief エコーキャンセラーを有効にします
    bool echo_cancellation = true;
    /// @brief 自動音量調整を有効にします
    bool auto_gain_control = true;
    /// @brief ノイズサプレッションを有効にします
    bool noise_suppression = true;
    /// @brief ハイパスフィルターを有効にします
    bool highpass_filter = true;
};

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_TYPES_HPP_ */
