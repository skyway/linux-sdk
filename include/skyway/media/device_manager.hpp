//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_DEVICE_MANAGER_HPP_
#define SKYWAY_MEDIA_DEVICE_MANAGER_HPP_

#include <api/create_peerconnection_factory.h>
#include <api/media_stream_interface.h>
#include <audio/audio_transport_impl.h>
#include <common_audio/resampler/include/push_resampler.h>
#include <modules/audio_device/include/audio_device.h>
#include <modules/audio_mixer/audio_mixer_impl.h>
#include <modules/video_capture/video_capture.h>
#include <pc/local_audio_source.h>

#include "skyway/global/logger.hpp"
#include "skyway/media/types.hpp"

namespace skyway {
namespace media {

/// @brief デバイスの情報を取得するクラス
class DeviceManager {
public:
    /// @brief 音声デバイス
    struct AudioDevice {
        int index;
        std::string name;
    };
    /// @brief 映像デバイス
    struct VideoDevice {
        int index;
        std::string name;
        std::string unique_id;
        /**
         * @brief 映像入力デバイスの列挙時に取得した先頭の設定候補です。
         * @deprecated この値は実際のキャプチャには利用されません。
         * キャプチャ設定を指定する場合は`StreamFactory::CaptureOptions`を利用してください。
         */
        [[deprecated(
            "This field is not used for actual capture. "
            "Use StreamFactory::CaptureOptions when specifying capture settings.")]] webrtc::
            VideoCaptureCapability capability;
    };
    /// @brief 利用する音声入力デバイスの一覧を取得します。
    static std::vector<AudioDevice> GetRecordDevices();

    /// @brief 利用する音声出力デバイスの一覧を取得します。
    static std::vector<AudioDevice> GetPlayoutDevices();

    /// @brief 利用する映像入力デバイスの一覧を取得します。
    static std::vector<VideoDevice> GetVideoDevices();

    /// @brief 利用する音声入力デバイスの設定します。
    static bool SetRecordingDevice(AudioDevice device);

    /// @brief 利用する音声出力デバイスの設定します。
    static bool SetPlayoutDevice(AudioDevice device);

    /// @cond INTERNAL_SECTION
    static void Init(AudioBackendType audio_backend,
                     const AudioProcessingOptions &audio_processing_options,
                     skyway::global::Logger *logger);
    static rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> GetPeerConnectionFactory();
    static void Dispose();
    static rtc::scoped_refptr<webrtc::AudioTrackInterface> CreateAudioTrack();
    static rtc::scoped_refptr<webrtc::AudioTrackInterface> CreateAudioTrack(
        rtc::scoped_refptr<webrtc::AudioSourceInterface> source);
    static rtc::scoped_refptr<webrtc::VideoTrackInterface> CreateVideoTrack(
        rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> source);
    static AudioBackendType GetAudioBackend();
    /// @endcond

private:
    static rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
    static rtc::scoped_refptr<webrtc::AudioDeviceModule> adm_;
    static std::unique_ptr<rtc::Thread> signaling_thread_;
    static std::unique_ptr<rtc::Thread> worker_thread_;
    static std::unique_ptr<webrtc::TaskQueueFactory> task_queue_factory_;
    static AudioBackendType audio_backend_;
};

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_DEVICE_MANAGER_HPP_ */
