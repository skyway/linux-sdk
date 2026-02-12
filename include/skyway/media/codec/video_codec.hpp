//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_CODEC_VIDEO_CODEC_HPP_
#define SKYWAY_MEDIA_CODEC_VIDEO_CODEC_HPP_

#include <map>
#include <string>

#include <api/video/video_codec_type.h>
#include <api/video_codecs/sdp_video_format.h>

namespace skyway {
namespace media {
namespace codec {

/**
 * @brief 映像コーデック
 * @details
 * SkyWayOptionsのRtp::Input::Video::enabledがtrueの時、Rtp::Input::Video::codecに設定するコーデック
 *
 * VideoSourceは`RtpCapturerVideoSource`のみ利用可能になり、その他のVideoSourceは利用できません。
 *
 */
struct VideoCodec {
    virtual ~VideoCodec() = default;
    /// @brief コーデック名
    virtual std::string Name() const = 0;
    /// @brief コーデックのパラメータ
    virtual std::map<std::string, std::string> Parameters() const = 0;
    /// @cond INTERNAL_SECTION
    virtual webrtc::VideoCodecType CodecType() const = 0;

    webrtc::SdpVideoFormat ToSdpVideoFormat() const {
        return webrtc::SdpVideoFormat(this->Name(), this->Parameters());
    }
    /// @endcond
};

}  // namespace codec
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_CODEC_VIDEO_CODEC_HPP_ */
