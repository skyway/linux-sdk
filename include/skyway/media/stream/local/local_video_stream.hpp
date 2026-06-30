//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_VIDEO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_VIDEO_STREAM_HPP_

#include <skyway/core/stream/local/video_stream.hpp>

#include "skyway/media/stream/abstract/stream_base.hpp"
#include "skyway/media/stream/interface/local/local_video_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace local {

class LocalVideoStream
    : public abstract::StreamBase<interface::local::LocalVideoStream,
                                  skyway::core::interface::LocalStream,
                                  skyway::core::stream::local::LocalVideoStream> {
public:
    /// @cond INTERNAL_SECTION
    LocalVideoStream(rtc::scoped_refptr<webrtc::VideoTrackInterface> track);
    LocalVideoStream(std::shared_ptr<skyway::core::stream::local::LocalVideoStream> core);
    /// @endcond

    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;
};

}  // namespace local
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_VIDEO_STREAM_HPP_
