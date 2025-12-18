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

namespace skyway {
namespace media {

/// @brief  オーディオバックエンドの種類
enum class AudioBackendType {
    /// @brief PulseAudioを使用します
    kPulseAudio,
    /// @brief オーディオバックエンドを使用しません
    kNone,
};

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
        webrtc::VideoCaptureCapability capability;
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
    static void Init(AudioBackendType audio_backend, skyway::global::Logger *logger);
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
