//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_AUDIO_INTERFACE_PCM_AUDIO_SOURCE_HPP_
#define SKYWAY_MEDIA_AUDIO_INTERFACE_PCM_AUDIO_SOURCE_HPP_

#include <cstdint>

#include "api/media_stream_interface.h"

namespace skyway {
namespace media {
namespace audio {
namespace interface {

/// @brief PCM音声ソース
class PcmAudioSource {
public:
    virtual ~PcmAudioSource() = default;

    /**
     * @brief PCM音声ソースのオプション
     * @details
     * PCM音声入力するためのオプションを表す構造体です。
     * PCM音声入力を行う際に、サンプリングレートやチャンネル数を指定する必要があります。
     */
    struct Options {
        /**
         * @brief サンプリングレート
         * @details
         * PCM音声データのサンプリングレート（Hz）を指定します。
         * サンプリングレートは100の倍数である必要があります。
         * 例: 8000, 16000, 32000, 44100, 48000
         */
        int sample_rate;

        /**
         * @brief チャンネル数
         * @details
         * PCM音声データのチャンネル数を指定します。
         * 1（モノラル）, 2（ステレオ）のみサポートします。
         */
        int channels;
    };

    /**
     * @brief PCM音声データを送信します。
     * @param buffer 10msごとのPCM音声データのバッファ
     * @details
     * PCM音声データをソースに送信します。
     * このメソッドは10msごとに呼び出す必要があります。
     */
    virtual bool PushPcmData(const int16_t* buffer) = 0;

    /// @cond INTERNAL_SECTION
    virtual rtc::scoped_refptr<webrtc::AudioSourceInterface> GetSource() = 0;
    /// @endcond
};
/// @endcond

}  // namespace interface
}  // namespace audio
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_AUDIO_INTERFACE_PCM_AUDIO_SOURCE_HPP_
