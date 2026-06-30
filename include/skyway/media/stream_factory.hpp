//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_FACTORY_HPP_
#define SKYWAY_MEDIA_STREAM_FACTORY_HPP_

#include "skyway/media/audio/interface/pcm_audio_source.hpp"
#include "skyway/media/device_manager.hpp"
#include "skyway/media/interface/capturer_video_source.hpp"
#include "skyway/media/stream/local/local_audio_stream.hpp"
#include "skyway/media/stream/local/local_data_stream.hpp"
#include "skyway/media/stream/local/local_video_stream.hpp"

namespace skyway {
namespace media {

/// @brief Streamの作成を行うクラス
class StreamFactory {
public:
    /**
     * @brief 映像入力デバイスからStreamを生成する際の希望設定
     * @details
     * width、height、framerate はいずれも希望値です。
     * 指定した値が必ず使われるとは限りません。
     */
    struct CaptureOptions {
        /// @brief 希望する映像の横幅
        int preferred_width = 640;
        /// @brief 希望する映像の縦幅
        int preferred_height = 480;
        /// @brief 希望するフレームレート
        int preferred_framerate = 30;
    };

    /// @brief LocalDataStreamを生成します。
    static std::shared_ptr<stream::local::LocalDataStream> CreateDataStream();

    /// @brief LocalAudioStreamを生成します。
    static std::shared_ptr<stream::local::LocalAudioStream> CreateAudioStream();

    /// @brief LocalAudioStreamを生成します。
    /// @param source StreamのソースになるPcmAudioSource
    static std::shared_ptr<stream::local::LocalAudioStream> CreateAudioStream(
        std::shared_ptr<audio::interface::PcmAudioSource> source);

    /// @brief LocalVideoStreamを生成します。
    /// @param track StreamのソースになるCapture
    static std::shared_ptr<stream::local::LocalVideoStream> CreateVideoStream(
        std::shared_ptr<interface::CapturerVideoSource> capturer);

    /// @brief LocalVideoStreamを生成します。
    /// @details
    /// 640x480 / 30fps を希望値として映像入力デバイスから生成します。
    /// 640x480 / 30fps が必ず使われるとは限りません。
    /// @param device StreamのソースになるVideoDevice
    static std::shared_ptr<stream::local::LocalVideoStream> CreateVideoStream(
        const DeviceManager::VideoDevice& device);

    /// @brief LocalVideoStreamを生成します。
    /// @details
    /// 映像入力デバイスに希望するキャプチャ設定を指定して生成します。
    /// 指定した値が必ず使われるとは限りません。
    /// @param device StreamのソースになるVideoDevice
    /// @param options 希望するキャプチャ設定
    static std::shared_ptr<stream::local::LocalVideoStream> CreateVideoStream(
        const DeviceManager::VideoDevice& device, const CaptureOptions& options);

    /// @cond INTERNAL_SECTION
    static std::shared_ptr<stream::local::LocalVideoStream> CreateVideoStream(
        rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> source);
    /// @endcond
};
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_STREAM_FACTORY_HPP_ */
