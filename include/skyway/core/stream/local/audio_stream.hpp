//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_LOCAL_AUDIO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_LOCAL_AUDIO_STREAM_HPP_

#include "skyway/content/audio/audio_track_sink_impl.hpp"
#include "skyway/content/audio/voice_detection/audio_level_calculator.hpp"
#include "skyway/core/interface/local_media_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace local {

class LocalAudioStream : public interface::LocalMediaStream {
public:
    LocalAudioStream(rtc::scoped_refptr<webrtc::AudioTrackInterface> track);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;

    ~LocalAudioStream() override;

    bool Enable() override;

    bool Disable() override;

    double GetAudioLevel() const;

private:
    void Dispose();

    std::atomic<bool> is_disposed_ = false;
    rtc::scoped_refptr<webrtc::AudioTrackInterface> track_;
    std::shared_ptr<content::audio::voice_detection::AudioLevelCalculator> audio_level_calculator_;
};

}  // namespace local
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif
