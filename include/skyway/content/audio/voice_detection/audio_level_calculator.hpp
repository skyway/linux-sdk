//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_AUDIO_LEVEL_CALCULATOR_HPP
#define SKYWAY_AUDIO_LEVEL_CALCULATOR_HPP

#include <atomic>
#include <chrono>
#include <mutex>

#include "skyway/content/audio/audio_data_listener.hpp"

namespace skyway {
namespace content {
namespace audio {
namespace voice_detection {

class AudioLevelCalculator : public content::audio::AudioDataListener {
public:
    AudioLevelCalculator();
    ~AudioLevelCalculator();

    void OnAudioData(size_t num_channels,
                     size_t num_frames,
                     int sample_rate,
                     std::vector<int16_t>& audio_data) override;

    double ComputeLevel();

    void Dispose();

private:
    std::atomic<bool> is_disposed_ = false;
    std::mutex ring_buffer_mutex_;
    const size_t num_of_frames_per_100ms = 10;
    std::vector<int16_t> ring_buffer_;
    size_t ring_buffer_index_ = 0;
    int16_t current_level_    = 0;
    int16_t abs_max_10_frames = 0;

    std::chrono::steady_clock::time_point on_audio_data_called_time_;
};

}  // namespace voice_detection
}  // namespace audio
}  // namespace content
}  // namespace skyway

#endif  // SKYWAY_AUDIO_LEVEL_CALCULATOR_HPP
