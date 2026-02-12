//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_CODEC_H264_HPP_
#define SKYWAY_MEDIA_CODEC_H264_HPP_

#include "skyway/media/codec/video_codec.hpp"

namespace skyway {
namespace media {
namespace codec {

inline constexpr std::string_view kDefaultH264ProfileLevelId = "42e01f";
/**
 * @brief H264コーデック
 * @details
 * Linux SDK
 * では現在H.264のデコードに対応していないため、このコーデックを利用したPublicationをSubscribeすることはできません。
 *
 * 各SDKが対応するコーデックについては[こちら](https://skyway.ntt.com/en/docs/user-guide/commons/codecs/)に記載しております。
 */
struct H264 : public VideoCodec {
    /**
     * @brief コンストラクタ
     * @details プロファイルレベルIDは42e01fが利用されます。
     */
    H264() : H264(std::string(kDefaultH264ProfileLevelId)) {}
    /**
     * @brief コンストラクタ
     * @param profile_level_id プロファイルレベルID
     */
    H264(const std::string& profile_level_id) {
        // clang-format off
        parameters = {
            // `1` is interleaved mode which is used in WebRTC.
            { "packetization-mode",      "1" },
            // `1` is asymmetrical mode which is used in WebRTC.
            { "level-asymmetry-allowed", "1" },
            { "profile-level-id",        profile_level_id }
        };
        // clang-format on
    }
    std::string Name() const override { return "H264"; }
    std::map<std::string, std::string> Parameters() const override { return parameters; }
    /// @cond INTERNAL_SECTION
    webrtc::VideoCodecType CodecType() const override { return webrtc::kVideoCodecH264; }
    /// @endcond
private:
    std::map<std::string, std::string> parameters;
};

}  // namespace codec
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_CODEC_H264_HPP_ */
