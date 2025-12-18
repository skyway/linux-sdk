//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_VIDEO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_VIDEO_STREAM_HPP_

#include <skyway/core/stream/local/video_stream.hpp>

namespace skyway {
namespace media {
namespace stream {
namespace local {

class LocalVideoStream : public skyway::core::stream::local::LocalVideoStream {
public:
    LocalVideoStream(rtc::scoped_refptr<webrtc::VideoTrackInterface> track);
};

}  // namespace local
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_VIDEO_STREAM_HPP_
