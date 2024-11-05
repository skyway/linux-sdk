//
//  capturer_video_source.hpp
//  skyway
//
//  Created by iorar on 2023/11/15.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_MEDIA_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_CAPTURER_VIDEO_SOURCE_HPP_

#include <media/base/adapted_video_track_source.h>
#include <modules/video_capture/video_capture.h>
#include <modules/video_capture/video_capture_factory.h>

namespace skyway {
namespace media {

class CapturerVideoSource : public rtc::AdaptedVideoTrackSource,
                            rtc::VideoSinkInterface<webrtc::VideoFrame> {
public:
    CapturerVideoSource();
    ~CapturerVideoSource();
    static rtc::scoped_refptr<CapturerVideoSource> Create(
        const std::string& device_unique_id, webrtc::VideoCaptureCapability device_capability);
    bool is_screencast() const override;
    absl::optional<bool> needs_denoising() const override;
    webrtc::MediaSourceInterface::SourceState state() const override;
    bool remote() const override;
    void OnFrame(const webrtc::VideoFrame& frame) override;

private:
    bool Init(const std::string& device_unique_id,
              webrtc::VideoCaptureCapability device_capability);
    void Destroy();
    rtc::scoped_refptr<webrtc::VideoCaptureModule> vcm_;
};

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_CAPTURER_VIDEO_SOURCE_ */
