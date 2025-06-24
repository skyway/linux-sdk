//
//  capturer_video_source.hpp
//  skyway
//
//  Created by iorar on 2023/11/15.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_V4L2_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_V4L2_CAPTURER_VIDEO_SOURCE_HPP_

#include "skyway/media/interface/capturer_video_source.hpp"

namespace skyway {
namespace media {

/// @cond INTERNAL_SECTION
class V4l2CapturerVideoSource : public interface::InternalCapturerVideoSource {
public:
    ~V4l2CapturerVideoSource();

    static rtc::scoped_refptr<V4l2CapturerVideoSource> Create(
        const std::string& device_unique_id, webrtc::VideoCaptureCapability device_capability);

    // rtc::VideoSourceInterface
    bool is_screencast() const override;
    absl::optional<bool> needs_denoising() const override;
    webrtc::MediaSourceInterface::SourceState state() const override;
    bool remote() const override;

    // rtc::VideoSinkInterface
    void OnFrame(const webrtc::VideoFrame& frame) override;

protected:
    V4l2CapturerVideoSource();

private:
    bool Init(const std::string& device_unique_id,
              webrtc::VideoCaptureCapability device_capability);
    void Destroy();
    rtc::scoped_refptr<webrtc::VideoCaptureModule> vcm_;
};
/// @endcond

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_CAPTURER_VIDEO_SOURCE_ */
