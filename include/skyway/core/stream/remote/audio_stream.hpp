//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_AUDIO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_AUDIO_STREAM_HPP_

#include <api/media_stream_interface.h>

#include "skyway/core/interface/remote_media_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace remote {

/// @brief RemoteMemberで扱うAudioStream
class RemoteAudioStream : public interface::RemoteMediaStream {
public:
    RemoteAudioStream(const std::string& id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack() const override;
    ~RemoteAudioStream();

    /// @cond INTERNAL_SECTION
    /// @brief Audioの再生を開始します。
    bool Enable() override;
    /// @brief Audioの再生を停止します。
    bool Disable() override;
    /// @endcond

private:
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track_;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_STREAM_REMOTE_AUDIO_STREAM_HPP_ */
