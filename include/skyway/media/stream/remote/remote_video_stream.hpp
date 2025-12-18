//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_VIDEO_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_VIDEO_STREAM_HPP_

#include <skyway/core/stream/remote/video_stream.hpp>

namespace skyway {
namespace media {
namespace stream {
namespace remote {

class RemoteVideoStream : public skyway::core::stream::remote::RemoteVideoStream {
public:
    RemoteVideoStream(std::shared_ptr<skyway::core::stream::remote::RemoteVideoStream> core);

private:
    std::shared_ptr<skyway::core::stream::remote::RemoteVideoStream> core_;
};

}  // namespace remote
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_VIDEO_STREAM_HPP_
