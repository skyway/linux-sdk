//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_AUDIO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_AUDIO_STREAM_HPP_

#include <skyway/core/stream/local/audio_stream.hpp>

namespace skyway {
namespace media {
namespace stream {
namespace local {

class LocalAudioStream : public skyway::core::stream::local::LocalAudioStream {
public:
    LocalAudioStream(rtc::scoped_refptr<webrtc::AudioTrackInterface> track);
};

}  // namespace local
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_AUDIO_STREAM_HPP_
