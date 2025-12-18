//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_CODEC_VP8_HPP_
#define SKYWAY_MEDIA_CODEC_VP8_HPP_

#include "skyway/media/codec/video_codec.hpp"

namespace skyway {
namespace media {
namespace codec {

/**
 * @brief VP8コーデック
 * @details ※この機能はβ版です。
 */
struct VP8 : public VideoCodec {
    std::string Name() const override { return "VP8"; }
    std::map<std::string, std::string> Parameters() const override { return {}; }
    /// @cond INTERNAL_SECTION
    webrtc::VideoCodecType CodecType() const override { return webrtc::kVideoCodecVP8; }
    /// @endcond
};

}  // namespace codec
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_CODEC_VP8_HPP_ */
