//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_VIDEO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_VIDEO_STREAM_HPP_

#include <skyway/core/stream/local/video_stream.hpp>

#include "skyway/media/stream/interface/local/local_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace local {

class LocalVideoStream : public LocalStream {
public:
    virtual ~LocalVideoStream()                                                 = default;
    virtual rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const = 0;
};

}  // namespace local
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_VIDEO_STREAM_HPP_
