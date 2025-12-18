//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_PASSTHROUGH_VIDEO_ENCODER_FACTORY_HPP_
#define SKYWAY_MEDIA_PASSTHROUGH_VIDEO_ENCODER_FACTORY_HPP_

#include "api/video_codecs/video_encoder_factory.h"
#include "skyway/media/rtp/passthrough_video_encoder.hpp"

namespace skyway {
namespace media {
namespace rtp {
/// @cond INTERNAL_SECTION
class PassthroughVideoEncoderFactory : public webrtc::VideoEncoderFactory {
public:
    PassthroughVideoEncoderFactory(
        std::shared_ptr<interface::RtpCapturerVideoSourceRepository> source_repo);
    std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const override;
    std::unique_ptr<webrtc::VideoEncoder> CreateVideoEncoder(
        const webrtc::SdpVideoFormat& format) override;

private:
    std::weak_ptr<interface::RtpCapturerVideoSourceRepository> source_repo_;
};
/// @endcond

}  // namespace rtp
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_PASSTHROUGH_VIDEO_ENCODER_FACTORY_HPP_
