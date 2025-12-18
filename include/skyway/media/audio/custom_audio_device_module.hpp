//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_AUDIO_CUSTOM_AUDIO_DEVICE_MODULE_HPP_
#define SKYWAY_MEDIA_AUDIO_CUSTOM_AUDIO_DEVICE_MODULE_HPP_

#include <atomic>
#include <cstdint>
#include <thread>

#include "modules/audio_device/include/audio_device.h"
#include "rtc_base/ref_counted_object.h"

namespace skyway {
namespace media {
namespace audio {

class CustomAudioDeviceModule : public webrtc::AudioDeviceModule {
public:
    static rtc::scoped_refptr<CustomAudioDeviceModule> Create(
        rtc::scoped_refptr<webrtc::AudioDeviceModule> pulse_audio_adm);

    CustomAudioDeviceModule(rtc::scoped_refptr<webrtc::AudioDeviceModule> pulse_audio_adm);

    ~CustomAudioDeviceModule() override;

    // webrtc::AudioDeviceModule
    int32_t ActiveAudioLayer(AudioLayer* audioLayer) const override;
    int32_t RegisterAudioCallback(webrtc::AudioTransport* audioCallback) override;
    int32_t Init() override;
    int32_t Terminate() override;
    bool Initialized() const override;
    int16_t PlayoutDevices() override;
    int16_t RecordingDevices() override;
    int32_t PlayoutDeviceName(uint16_t index,
                              char name[webrtc::kAdmMaxDeviceNameSize],
                              char guid[webrtc::kAdmMaxGuidSize]) override;
    int32_t RecordingDeviceName(uint16_t index,
                                char name[webrtc::kAdmMaxDeviceNameSize],
                                char guid[webrtc::kAdmMaxGuidSize]) override;
    int32_t SetPlayoutDevice(uint16_t index) override;
    int32_t SetPlayoutDevice(WindowsDeviceType) override { return -1; }
    int32_t SetRecordingDevice(uint16_t index) override;
    int32_t SetRecordingDevice(WindowsDeviceType) override { return -1; }
    int32_t PlayoutIsAvailable(bool* available) override;
    int32_t InitPlayout() override;
    bool PlayoutIsInitialized() const override;
    int32_t RecordingIsAvailable(bool* available) override;
    int32_t InitRecording() override;
    bool RecordingIsInitialized() const override;
    int32_t StartPlayout() override;
    int32_t StopPlayout() override;
    bool Playing() const override;
    int32_t StartRecording() override;
    int32_t StopRecording() override;
    bool Recording() const override;
    int32_t InitSpeaker() override;
    bool SpeakerIsInitialized() const override;
    int32_t InitMicrophone() override;
    bool MicrophoneIsInitialized() const override;
    int32_t SpeakerVolumeIsAvailable(bool* available) override;
    int32_t SetSpeakerVolume(uint32_t volume) override;
    int32_t SpeakerVolume(uint32_t* volume) const override;
    int32_t MaxSpeakerVolume(uint32_t* maxVolume) const override;
    int32_t MinSpeakerVolume(uint32_t* minVolume) const override;
    int32_t MicrophoneVolumeIsAvailable(bool* available) override;
    int32_t SetMicrophoneVolume(uint32_t volume) override;
    int32_t MicrophoneVolume(uint32_t* volume) const override;
    int32_t MaxMicrophoneVolume(uint32_t* maxVolume) const override;
    int32_t MinMicrophoneVolume(uint32_t* minVolume) const override;
    int32_t SpeakerMuteIsAvailable(bool* available) override;
    int32_t SetSpeakerMute(bool enable) override;
    int32_t SpeakerMute(bool* enabled) const override;
    int32_t MicrophoneMuteIsAvailable(bool* available) override;
    int32_t SetMicrophoneMute(bool enable) override;
    int32_t MicrophoneMute(bool* enabled) const override;
    int32_t StereoPlayoutIsAvailable(bool* available) const override;
    int32_t SetStereoPlayout(bool enable) override;
    int32_t StereoPlayout(bool* enabled) const override;
    int32_t StereoRecordingIsAvailable(bool* available) const override;
    int32_t SetStereoRecording(bool enable) override;
    int32_t StereoRecording(bool* enabled) const override;
    int32_t PlayoutDelay(uint16_t* delayMS) const override;

    // Android built-ins (not used; return defaults)
    bool BuiltInAECIsAvailable() const override { return false; }
    bool BuiltInAGCIsAvailable() const override { return false; }
    bool BuiltInNSIsAvailable() const override { return false; }
    int32_t EnableBuiltInAEC(bool) override { return -1; }
    int32_t EnableBuiltInAGC(bool) override { return -1; }
    int32_t EnableBuiltInNS(bool) override { return -1; }

    bool UsingDummySpeaker() const { return use_dummy_speaker_; }

private:
    void PlayoutPumpLoop_();

    rtc::scoped_refptr<webrtc::AudioDeviceModule> pulse_audio_adm_;
    std::atomic<webrtc::AudioTransport*> transport_ = nullptr;
    std::atomic<bool> inited_                       = false;
    std::atomic<bool> playout_inited_               = false;
    std::atomic<bool> recording_inited_             = false;
    std::atomic<bool> playing_                      = false;
    std::atomic<bool> recording_                    = false;
    std::atomic<bool> use_dummy_speaker_            = false;
    std::thread playout_thread_;
    std::atomic<bool> stop_playout_thread_ = false;
    std::atomic<bool> stereo_playout_      = true;
    std::atomic<bool> stereo_recording_    = true;
};

}  // namespace audio
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_AUDIO_CUSTOM_AUDIO_DEVICE_MODULE_HPP_
