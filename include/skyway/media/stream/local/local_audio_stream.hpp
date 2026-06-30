//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_AUDIO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_AUDIO_STREAM_HPP_

#include <skyway/core/stream/local/audio_stream.hpp>

#include "skyway/media/stream/abstract/stream_base.hpp"
#include "skyway/media/stream/interface/local/local_audio_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace local {

class LocalAudioStream
    : public abstract::StreamBase<interface::local::LocalAudioStream,
                                  skyway::core::interface::LocalStream,
                                  skyway::core::stream::local::LocalAudioStream> {
public:
    /// @cond INTERNAL_SECTION
    LocalAudioStream(rtc::scoped_refptr<webrtc::AudioTrackInterface> track);
    LocalAudioStream(std::shared_ptr<skyway::core::stream::local::LocalAudioStream> core);
    /// @endcond

    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;
};

}  // namespace local
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_AUDIO_STREAM_HPP_
