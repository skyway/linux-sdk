//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_AUDIO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_AUDIO_STREAM_HPP_

#include <mutex>
#include <unordered_set>

#include <api/media_stream_interface.h>
#include <skyway/core/stream/remote/audio_stream.hpp>

#include "skyway/media/audio/interface/audio_frame.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace remote {

class RemoteAudioStream : public skyway::core::stream::remote::RemoteAudioStream {
public:
    class Listener {
    public:
        virtual ~Listener() = default;

        /// @brief PCM音声データを受け取ります。
        /// @param frame 音声フレーム
        /// @details
        /// PCM音声データが取得された際に呼び出されます
        virtual void OnTrackData(const audio::interface::AudioFrame& frame) = 0;
    };

    RemoteAudioStream(std::shared_ptr<skyway::core::stream::remote::RemoteAudioStream> core);

    void RegisterListener(std::shared_ptr<Listener> listener);
    void UnregisterListener(std::shared_ptr<Listener> listener);

private:
    class PcmAudioTrackSink : public webrtc::AudioTrackSinkInterface {
    public:
        PcmAudioTrackSink(std::shared_ptr<Listener> listener);
        void OnData(const void* audio_data,
                    int bits_per_sample,
                    int sample_rate,
                    size_t number_of_channels,
                    size_t number_of_frames,
                    absl::optional<int64_t>) override;

    private:
        std::shared_ptr<RemoteAudioStream::Listener> listener_;
    };

    std::shared_ptr<skyway::core::stream::remote::RemoteAudioStream> core_;
    std::unordered_map<std::shared_ptr<Listener>, std::shared_ptr<PcmAudioTrackSink>> sinks_;
    std::mutex sinks_mtx_;
};

}  // namespace remote
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_AUDIO_STREAM_HPP_
