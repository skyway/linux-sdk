//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_STREAM_HPP_

#include <skyway/core/interface/remote_stream.hpp>

#include "skyway/media/stream/interface/stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace remote {

class RemoteStream : public Stream {
public:
    virtual ~RemoteStream() = default;

    /// @cond INTERNAL_SECTION
    virtual std::shared_ptr<skyway::core::interface::RemoteStream> GetCore() = 0;
    /// @endcond
};

}  // namespace remote
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_STREAM_HPP_
