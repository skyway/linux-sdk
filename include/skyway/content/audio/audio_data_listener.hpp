//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CONTENT_AUDIO_DATA_LISTENER_HPP
#define SKYWAY_CONTENT_AUDIO_DATA_LISTENER_HPP

#include <vector>
#include <stdint.h>

namespace skyway {
namespace content {
namespace audio {

class AudioDataListener {
public:
    virtual void onAudioData(size_t num_channels, size_t num_frames, int sample_rate, std::vector<int16_t>& audio_data) = 0;

};

}
}
}

#endif //SKYWAY_CONTENT_AUDIO_DATA_LISTENER_HPP
