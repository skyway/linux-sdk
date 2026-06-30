//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_LOCAL_VIDEO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_LOCAL_VIDEO_STREAM_HPP_

#include <api/media_stream_interface.h>

#include "skyway/core/interface/local_media_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace local {

using LocalMediaStream = interface::LocalMediaStream;

class LocalVideoStream : public LocalMediaStream {
public:
    LocalVideoStream(rtc::scoped_refptr<webrtc::VideoTrackInterface> track);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;

    bool Enable() override;

    bool Disable() override;

    void SetContentHint(webrtc::VideoTrackInterface::ContentHint content_hint);

private:
    rtc::scoped_refptr<webrtc::VideoTrackInterface> track_;
};

}  // namespace local
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif
