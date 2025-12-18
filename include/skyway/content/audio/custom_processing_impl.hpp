//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CONTENT_CUSTOM_PROCESSING_IMPL_HPP
#define SKYWAY_CONTENT_CUSTOM_PROCESSING_IMPL_HPP

#include <modules/audio_processing/include/audio_processing.h>
#include "audio_data_forwarder.hpp"

namespace skyway {
namespace content {
namespace audio {

class CustomProcessingImpl : public webrtc::CustomProcessing {
public:
    CustomProcessingImpl(std::shared_ptr<AudioDataForwarder> audio_data_forwarder);
    ~CustomProcessingImpl();

    void Initialize(int sample_rate_hz, int num_channels) override;

    // Processes the given capture or render signal.
    void Process(webrtc::AudioBuffer *audio) override;

    // Returns a string representation of the module state.
    std::string ToString() const override;
private:
    webrtc::StreamConfig stream_config_;
    std::shared_ptr<AudioDataForwarder> audio_data_forwarder_;
};


}
}
} // skyway

#endif //SKYWAY_CONTENT_CUSTOM_PROCESSING_IMPL_HPP
