//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_LOCAL_MEDIA_STREAM_HPP_
#define SKYWAY_CORE_INTERFACE_LOCAL_MEDIA_STREAM_HPP_

#include <api/media_stream_interface.h>

#include "skyway/core/interface/local_stream.hpp"

namespace skyway {
namespace core {
namespace interface {

class LocalMediaStream : public LocalStream {
public:
    virtual ~LocalMediaStream() = default;

    virtual rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const = 0;

protected:
    LocalMediaStream(model::ContentType content_type);
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
