//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_AUDIO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_AUDIO_STREAM_HPP_

#include <mutex>
#include <unordered_set>

#include <api/media_stream_interface.h>
#include <skyway/core/stream/remote/audio_stream.hpp>

#include "skyway/media/audio/interface/audio_frame.hpp"
#include "skyway/media/stream/interface/remote/remote_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace remote {

class RemoteAudioStream : public RemoteStream {
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

    virtual ~RemoteAudioStream() = default;

    /// @brief RemoteAudioStream::Listenerを登録します。
    /// @param listener PCM音声データが取得された際に呼ばれるイベントリスナー
    virtual void RegisterListener(std::shared_ptr<Listener> listener) = 0;

    /// @brief イベントリスナーの登録を解除します。
    /// @param listener 登録解除するイベントリスナー
    virtual void UnregisterListener(std::shared_ptr<Listener> listener) = 0;

    virtual rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const = 0;
};

}  // namespace remote
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_AUDIO_STREAM_HPP_
