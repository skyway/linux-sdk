//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_AUDIO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_AUDIO_STREAM_HPP_

#include "skyway/content/audio/audio_track_sink_impl.hpp"
#include "skyway/content/audio/voice_detection/audio_level_calculator.hpp"
#include "skyway/core/interface/remote_media_stream.hpp"

namespace rtc {
class Thread;
}

namespace skyway {
namespace core {
namespace stream {
namespace remote {

class RemoteAudioStream : public interface::RemoteMediaStream {
public:
    RemoteAudioStream(const std::string& id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track)
        : RemoteAudioStream(id, track, nullptr) {}
    RemoteAudioStream(const std::string& id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track,
                      rtc::Thread* signaling_thread);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack() const override;
    ~RemoteAudioStream();

    bool Enable() override;

    bool Disable() override;

    double GetAudioLevel() const;

    void SetVolume(double volume);
    void Dispose() override;

private:
    std::atomic<bool> is_disposed_ = false;
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track_;
    rtc::Thread* signaling_thread_ = nullptr;
    std::unique_ptr<content::audio::AudioTrackSinkImpl> audio_track_sink_impl_;
    std::shared_ptr<content::audio::voice_detection::AudioLevelCalculator> audio_level_calculator_;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif
