//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_AUDIO_TRACK_SINK_IMPL_HPP
#define SKYWAY_AUDIO_TRACK_SINK_IMPL_HPP

#include <api/media_stream_interface.h>
#include "audio_data_forwarder.hpp"

namespace skyway {
namespace content {
namespace audio {
class AudioTrackSinkImpl: public AudioDataForwarder, public webrtc::AudioTrackSinkInterface {

public:
    AudioTrackSinkImpl(rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track);
    ~AudioTrackSinkImpl();

    void OnData(const void* audio_data,
                int bits_per_sample,
                int sample_rate,
                size_t number_of_channels,
                size_t number_of_frames) override;

};
} // audio
} // content
} // skyway

#endif //SKYWAY_AUDIO_TRACK_SINK_IMPL_HPP
