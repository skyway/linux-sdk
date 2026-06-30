//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_VIDEO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_VIDEO_STREAM_HPP_

#include <api/media_stream_interface.h>

#include "skyway/core/interface/remote_media_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace remote {

class RemoteVideoStream : public interface::RemoteMediaStream {
public:
    RemoteVideoStream(const std::string& id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track);
    ~RemoteVideoStream();
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack() const override;

    bool Enable() override;

    bool Disable() override;

private:
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track_;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif
