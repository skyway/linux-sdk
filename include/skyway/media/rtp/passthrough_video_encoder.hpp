//
//  passthrough_video_encoder.hpp
//  skyway
//
//  Created by sandabu on 2025/5/21.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//
#ifndef SKYWAY_MEDIA_PASSTHROUGH_VIDEO_ENCODER_HPP_
#define SKYWAY_MEDIA_PASSTHROUGH_VIDEO_ENCODER_HPP_

#include <api/video_codecs/video_encoder.h>
#include <api/video_codecs/video_encoder_factory.h>
#include <modules/rtp_rtcp/source/rtcp_sender.h>
#include <functional>
#include <memory>

#include "skyway/global/interface/worker.hpp"
#include "skyway/media/rtp/interface/rtp_capturer_video_source_repository.hpp"

namespace skyway {
namespace media {
namespace rtp {
/// @cond INTERNAL_SECTION
class PassthroughVideoEncoder : public webrtc::VideoEncoder {
public:
    PassthroughVideoEncoder(
        std::shared_ptr<interface::RtpCapturerVideoSourceRepository> source_repo);
    ~PassthroughVideoEncoder();
    int InitEncode(const webrtc::VideoCodec* codec_settings, const Settings& settings) override;
    int32_t Encode(const webrtc::VideoFrame& frame,
                   const std::vector<webrtc::VideoFrameType>* frame_types) override;

    void SetRates(const webrtc::VideoEncoder::RateControlParameters& parameters) override;

    int32_t RegisterEncodeCompleteCallback(webrtc::EncodedImageCallback* callback) override;

    int32_t Release() override;

    webrtc::VideoEncoder::EncoderInfo GetEncoderInfo() const override;

private:
    std::shared_ptr<interface::RtpCapturerVideoSource> video_source_ = nullptr;
    webrtc::EncodedImageCallback* callback_                          = nullptr;
    std::weak_ptr<interface::RtpCapturerVideoSourceRepository> source_repo_;

public:
    friend class PassthroughVideoEncoderTest;
};
/// @endcond

#endif  // SKYWAY_MEDIA_PASSTHROUGH_VIDEO_ENCODER_HPP_

}  // namespace rtp
}  // namespace media
}  // namespace skyway
