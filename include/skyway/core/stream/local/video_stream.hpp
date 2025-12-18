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

/// @brief LocalPersonで扱うVideoStream
class LocalVideoStream : public LocalMediaStream {
public:
    LocalVideoStream(rtc::scoped_refptr<webrtc::VideoTrackInterface> track);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;

    /// @cond INTERNAL_SECTION
    /// @brief Videoの再生を開始します。
    bool Enable() override;
    /// @brief Videoの再生を停止します。
    bool Disable() override;
    /// @brief ContentHintを設定します。
    void SetContentHint(webrtc::VideoTrackInterface::ContentHint content_hint);
    /// @endcond

private:
    rtc::scoped_refptr<webrtc::VideoTrackInterface> track_;
};

}  // namespace local
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_STREAM_LOCAL_VIDEO_STREAM_HPP_ */
