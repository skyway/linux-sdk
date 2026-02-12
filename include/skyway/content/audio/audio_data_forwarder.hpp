//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CONTENT_AUDIO_DATA_FORWARDER_HPP
#define SKYWAY_CONTENT_AUDIO_DATA_FORWARDER_HPP

#include "audio_data_listener.hpp"
#include <mutex>
#include <set>
#include <memory>

namespace skyway {
namespace content {
namespace audio {

class AudioDataForwarder {
public:
    AudioDataForwarder();
    ~AudioDataForwarder();
    void OnAudioData(size_t num_channels, size_t num_frames, int sample_rate, std::vector<int16_t>& audio_data);
    void AddAudioDataListener(std::shared_ptr<AudioDataListener> listener);
    void RemoveAudioDataListener(std::shared_ptr<AudioDataListener> listener);
    void ClearAudioDataListeners();
private:
    std::vector<std::shared_ptr<AudioDataListener>> audio_data_listeners_;
    std::mutex audio_data_listeners_mutex_;
};
}
}
}

#endif //SKYWAY_CONTENT_AUDIO_DATA_FORWARDER_HPP
