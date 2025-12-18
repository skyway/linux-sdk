//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CONTENT_AUDIO_PROCESSING_MANAGER_HPP
#define SKYWAY_CONTENT_AUDIO_PROCESSING_MANAGER_HPP

#include <modules/audio_processing/include/audio_processing.h>
#include "audio_data_forwarder.hpp"
#include "skyway/global/interface/logger.hpp"

namespace skyway {
namespace content {
namespace audio {

class AudioProcessingManager {
public:
    static rtc::scoped_refptr<webrtc::AudioProcessing> CreateAudioProcessing();

    static void SetAudioDataListener(std::shared_ptr<AudioDataListener> listener);

    static void RemoveAudioDataListener();

    static bool SetEchoCancellerMobileModeEnabled(bool enabled);

    static bool SetEchoCancellerEnabled(bool is_enabled);

    static bool SetNoiseSuppressionEnabled(bool is_enabled);

    static void Dispose();

private:
    static rtc::scoped_refptr<webrtc::AudioProcessing> audio_processing_;
    static std::shared_ptr<AudioDataForwarder> audio_data_forwarder_;

};

}
}
}

#endif //SKYWAY_CONTENT_AUDIO_PROCESSING_MANAGER_HPP
