//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_STREAM_HPP_

#include <skyway/core/interface/local_stream.hpp>

#include "skyway/media/stream/interface/stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace local {

class LocalStream : public Stream {
public:
    virtual ~LocalStream() = default;

    /// @cond INTERNAL_SECTION
    virtual std::shared_ptr<skyway::core::interface::LocalStream> GetCore() = 0;
    /// @endcond
};

}  // namespace local
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_STREAM_HPP_
