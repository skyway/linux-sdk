//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_VIDEO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_VIDEO_STREAM_HPP_

#include <skyway/core/stream/remote/video_stream.hpp>

#include "skyway/media/stream/interface/remote/remote_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace remote {

class RemoteVideoStream : public RemoteStream {
public:
    virtual ~RemoteVideoStream()                                                = default;
    virtual rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const = 0;
};

}  // namespace remote
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_VIDEO_STREAM_HPP_
