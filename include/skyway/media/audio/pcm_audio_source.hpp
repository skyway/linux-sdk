//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_AUDIO_PCM_AUDIO_SOURCE_HPP_
#define SKYWAY_MEDIA_AUDIO_PCM_AUDIO_SOURCE_HPP_

#include <mutex>
#include <vector>
#include "absl/types/optional.h"

#include "api/audio_options.h"
#include "api/media_stream_interface.h"
#include "rtc_base/ref_counted_object.h"

#include "skyway/media/audio/interface/pcm_audio_source.hpp"

namespace skyway {
namespace media {
namespace audio {

class PcmAudioSource : public interface::PcmAudioSource {
public:
    /**
     * @brief PCM音声ソースのインスタンスを作成します。
     * @details
     * この機能を利用するためには`Context::Setup`におけるSkyWayOptionsの`audio_backend`を`AudioBackendType::kNone`に設定する必要があります。
     * @param options オプション
     * @return std::shared_ptr<PcmAudioSource>
     */
    static std::shared_ptr<PcmAudioSource> Create(
        const interface::PcmAudioSource::Options& options);

    /// @cond INTERNAL_SECTION
    PcmAudioSource(const interface::PcmAudioSource::Options& options);
    rtc::scoped_refptr<webrtc::AudioSourceInterface> GetSource() override;
    /// @endcond

    bool PushPcmData(const int16_t* buffer) override;

private:
    class PcmInternalAudioSource : public webrtc::AudioSourceInterface {
    public:
        PcmInternalAudioSource(const interface::PcmAudioSource::Options& options);
        ~PcmInternalAudioSource() override = default;

        // webrtc::MediaSourceInterface
        webrtc::MediaSourceInterface::SourceState state() const override;
        bool remote() const override { return false; };
        void RegisterObserver(webrtc::ObserverInterface* observer) override;
        void UnregisterObserver(webrtc::ObserverInterface* observer) override;

        // webrtc::AudioSourceInterface
        void AddSink(webrtc::AudioTrackSinkInterface* sink) override;
        void RemoveSink(webrtc::AudioTrackSinkInterface* sink) override;

        const cricket::AudioOptions options() const override { return cricket::AudioOptions{}; }

        bool PushPcmData(const int16_t* buffer);

    private:
        mutable std::mutex observer_mtx_;
        mutable std::mutex sinks_mtx_;
        std::vector<webrtc::ObserverInterface*> ms_observers_;
        std::vector<webrtc::AudioTrackSinkInterface*> sinks_;
        int sample_rate_;
        int channels_;
    };

    rtc::scoped_refptr<PcmInternalAudioSource> internal_source_;
};

}  // namespace audio
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_AUDIO_PCM_AUDIO_SOURCE_HPP_
