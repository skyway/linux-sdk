//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_VIDEO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_VIDEO_STREAM_HPP_

#include <skyway/core/stream/remote/video_stream.hpp>
#include <skyway/media/stream/interface/remote/remote_video_stream.hpp>

#include "skyway/media/stream/abstract/stream_base.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace remote {

class RemoteVideoStream
    : public abstract::StreamBase<interface::remote::RemoteVideoStream,
                                  skyway::core::interface::RemoteStream,
                                  skyway::core::stream::remote::RemoteVideoStream> {
public:
    /// @cond INTERNAL_SECTION
    RemoteVideoStream(std::shared_ptr<skyway::core::stream::remote::RemoteVideoStream> core);
    /// @endcond
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;
};

}  // namespace remote
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_VIDEO_STREAM_HPP_
