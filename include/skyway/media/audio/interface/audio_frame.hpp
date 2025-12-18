//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_AUDIO_INTERFACE_AUDIO_FRAME_HPP_
#define SKYWAY_MEDIA_AUDIO_INTERFACE_AUDIO_FRAME_HPP_

#include <cstdint>
#include <string>

namespace skyway {
namespace media {
namespace audio {
namespace interface {

/**
 * @brief オーディオフレーム
 * @details
 * PCM形式の音声データとそのパラメータを表す構造体です。
 */
struct AudioFrame {
    /** @brief 音声データのバッファ
     * @details
     * PCM音声データのバッファへのポインタです。
     */
    const void* buffer;

    /** @brief サンプリングレート
     * @details
     * 音声データのサンプリングレート（Hz）を表します。
     */
    int sample_rate;

    /** @brief チャンネル数
     * @details
     * 音声データのチャンネル数を表します。
     */
    int channels;

    /** @brief チャンネルあたりのサンプル数
     * @details
     * 音声データのチャンネルあたりのサンプル数を表します。
     */
    int samples_per_channel;

    /** @brief 1サンプルあたりのビット数
     * @details
     * 音声データの1サンプルあたりのビット数を表します。通常は16ビットが使用されます。
     */
    int bits_per_sample;
};

}  // namespace interface
}  // namespace audio
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_AUDIO_INTERFACE_AUDIO_FRAME_HPP_
