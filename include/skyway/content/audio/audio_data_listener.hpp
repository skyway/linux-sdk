//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CONTENT_AUDIO_DATA_LISTENER_HPP
#define SKYWAY_CONTENT_AUDIO_DATA_LISTENER_HPP

#include <vector>
#include <stdint.h>
#include <stddef.h>

namespace skyway {
namespace content {
namespace audio {

class AudioDataListener {
public:
    AudioDataListener(int priority = 0) : priority_(priority) {}

    virtual void OnAudioData(size_t num_channels, size_t num_frames, int sample_rate, std::vector<int16_t>& audio_data) = 0;
    virtual int GetPriority() const {
        return priority_;
    }
protected:
    const int priority_;
};

}
}
}

#endif //SKYWAY_CONTENT_AUDIO_DATA_LISTENER_HPP
