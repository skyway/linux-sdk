//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_V4L2_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_V4L2_CAPTURER_VIDEO_SOURCE_HPP_

#include <api/video/video_sink_interface.h>
#include <modules/video_capture/video_capture.h>

#include "skyway/media/interface/capturer_video_source.hpp"

namespace skyway {
namespace media {

/// @cond INTERNAL_SECTION

class V4l2CapturerVideoSource : public interface::InternalCapturerVideoSource {
public:
    class VideoSinkCallback : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
    public:
        VideoSinkCallback(V4l2CapturerVideoSource* source) : source_(source){};
        // rtc::VideoSinkInterface
        void OnFrame(const webrtc::VideoFrame& frame) { source_->OnFrame(frame); }

    private:
        V4l2CapturerVideoSource* source_ = nullptr;
    };
    ~V4l2CapturerVideoSource();

    static rtc::scoped_refptr<V4l2CapturerVideoSource> Create(
        const std::string& device_unique_id, webrtc::VideoCaptureCapability device_capability);

    // rtc::VideoSourceInterface
    bool is_screencast() const override;
    absl::optional<bool> needs_denoising() const override;
    webrtc::MediaSourceInterface::SourceState state() const override;
    bool remote() const override;

protected:
    V4l2CapturerVideoSource();

private:
    bool Init(const std::string& device_unique_id,
              webrtc::VideoCaptureCapability device_capability);
    void Destroy();
    rtc::scoped_refptr<webrtc::VideoCaptureModule> vcm_     = nullptr;
    std::unique_ptr<VideoSinkCallback> video_sink_callback_ = nullptr;
};
/// @endcond

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_CAPTURER_VIDEO_SOURCE_ */
