//
//  rtp_capturer_video_source.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2025/06/30.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_RTP_INTERFACE_RTP_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_RTP_INTERFACE_RTP_CAPTURER_VIDEO_SOURCE_HPP_

#include <api/video_codecs/video_encoder.h>

#include "skyway/media/interface/capturer_video_source.hpp"

namespace skyway {
namespace media {
namespace rtp {
namespace interface {

/// @brief RTPキャプチャビデオソースのオプション
/// @details ※この機能はβ版です。
struct RtpCapturerVideoSourceOptions {
    /**
     * @brief RTPパケットを受け付けるUDPサーバのIPv4アドレス
     * @details
     * RTPパケットを受信するためにSkyWay内部でUDPサーバをLISTENするためのIPv4アドレスです。
     *
     * 例: Gstreamerにおいて、`udpsink host=127.0.0.1　port=50000`であれば"127.0.0.1"を指定します。
     */
    std::string recv_rtp_ipv4;
    /**
     * @brief RTPパケットを受け付けるUDPサーバのPort番号
     * @details
     * RTPパケットを受信するためにSkyWay内部でUDPサーバをLISTENするためのPort番号です。
     *
     * 例: Gstreamerにおいて、`udpsink host=127.0.0.1　port=50000`であれば50000を指定します。
     */
    int recv_rtp_port = 0;
};
/**
 * @brief RTPキャプチャビデオソース
 * @details
 * ※この機能はβ版です。
 *
 * この機能を利用するためには`Context::Setup`におけるSkyWayOptionsのRtp::Input::Videoにおいて、`enabled`を`true`に設定し、`codec`に適切なコーデックを設定する必要があります。
 *
 * また、RTP映像入力モードが有効な場合は、他のVideoSourceは利用できません。
 */
class RtpCapturerVideoSource : public media::interface::CapturerVideoSource {
public:
    /**
     * @brief デストラクタ
     * @details
     * SkyWay内部でも所有権を管理しており、`Context::Dispose()`で破棄されます。
     */
    virtual ~RtpCapturerVideoSource() = default;

    /**
     * @brief UDPサーバを起動し、RTPパケットの受信を開始します。
     * @details
     * このメソッドを呼び出すことで、SkyWay内部でUDPサーバが起動し、指定されたIPv4アドレスとPort番号でRTPパケットの受信を開始します。
     *
     * Publish前・後どちらでも呼び出すことができます。
     *
     * @return 成功可否
     */
    virtual bool StartReceiving() = 0;

    /**
     * @brief UDPサーバを停止し、RTPパケットの受信を停止します。
     * @details
     * このメソッドを呼び出すことで、SkyWay内部で起動しているUDPサーバを停止し、RTPパケットの受信を停止します。
     *
     * 再度`StartReceiving()`を呼び出すことで、再度RTPパケットの受信を開始できます。
     *
     * アプリ側で`RtpCapturerVideoSource`を破棄前にこのメソッドを呼び出すことを推奨します。
     *
     * @return 成功可否
     */
    virtual bool StopReceiving() = 0;

    /// @cond INTERNAL_SECTION
    virtual std::optional<uint8_t> GetFrameId()                            = 0;
    virtual void RegisterCallback(webrtc::EncodedImageCallback* callback)  = 0;
    virtual std::string Endpoint() const                                   = 0;
    virtual void OnEncoderReleased(webrtc::EncodedImageCallback* callback) = 0;
    /// @endcond
};

}  // namespace interface
}  // namespace rtp
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_RTP_INTERFACE_RTP_CAPTURER_VIDEO_SOURCE_HPP_ */
