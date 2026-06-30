//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_AUDIO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_AUDIO_STREAM_HPP_

#include <mutex>
#include <unordered_map>

#include <api/media_stream_interface.h>
#include <skyway/core/stream/remote/audio_stream.hpp>

#include "skyway/media/audio/interface/audio_frame.hpp"
#include "skyway/media/stream/abstract/stream_base.hpp"
#include "skyway/media/stream/interface/remote/remote_audio_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace remote {

class RemoteAudioStream
    : public abstract::StreamBase<interface::remote::RemoteAudioStream,
                                  skyway::core::interface::RemoteStream,
                                  skyway::core::stream::remote::RemoteAudioStream> {
public:
    /// @cond INTERNAL_SECTION
    RemoteAudioStream(std::shared_ptr<skyway::core::stream::remote::RemoteAudioStream> core);
    /// @endcond

    /// @copydoc skyway::media::stream::interface::remote::RemoteAudioStream::RegisterListener
    void RegisterListener(
        std::shared_ptr<interface::remote::RemoteAudioStream::Listener> listener) override;

    /// @copydoc skyway::media::stream::interface::remote::RemoteAudioStream::UnregisterListener
    void UnregisterListener(
        std::shared_ptr<interface::remote::RemoteAudioStream::Listener> listener) override;
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;

private:
    class PcmAudioTrackSink : public webrtc::AudioTrackSinkInterface {
    public:
        explicit PcmAudioTrackSink(
            std::shared_ptr<interface::remote::RemoteAudioStream::Listener> listener);
        void OnData(const void* audio_data,
                    int bits_per_sample,
                    int sample_rate,
                    size_t number_of_channels,
                    size_t number_of_frames,
                    absl::optional<int64_t>) override;

    private:
        std::shared_ptr<interface::remote::RemoteAudioStream::Listener> listener_;
    };

    std::unordered_map<std::shared_ptr<interface::remote::RemoteAudioStream::Listener>,
                       std::shared_ptr<PcmAudioTrackSink>>
        sinks_;
    std::mutex sinks_mtx_;
};

}  // namespace remote
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_AUDIO_STREAM_HPP_
