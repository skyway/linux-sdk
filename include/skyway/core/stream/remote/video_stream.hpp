//
//  video_stream.hpp
//  skyway
//
//  Created by sandabu on 2022/02/01.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_VIDEO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_VIDEO_STREAM_HPP_

#include <api/media_stream_interface.h>

#include "skyway/core/interface/remote_media_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace remote {

/// @brief RemoteMemberで扱うVideoStream
class RemoteVideoStream : public interface::RemoteMediaStream {
public:
    RemoteVideoStream(const std::string& id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack() const override;

    /// @cond INTERNAL_SECTION
    /// @brief Videoの再生を開始します。
    bool Enable() override;
    /// @brief Videoの再生を停止します。
    bool Disable() override;
    /// @endcond

private:
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track_;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_STREAM_REMOTE_VIDEO_STREAM_HPP_ */
