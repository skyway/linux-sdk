//
//  rtcp_transport.hpp
//  skyway
//
//  Created by sandabu on 2025/06/06.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_RTP_RTCP_TRANSPORT_HPP_
#define SKYWAY_MEDIA_RTP_RTCP_TRANSPORT_HPP_

#include <cstdint>
#include <string>

#include <modules/rtp_rtcp/include/rtp_rtcp_defines.h>

#include <api/call/transport.h>

#include "skyway/media/rtp/interface/rtp_capturer_video_source.hpp"
#include "skyway/network/interface/udp_client.hpp"

namespace skyway {
namespace media {
namespace rtp {
/// @cond INTERNAL_SECTION
class RtcpTransport : public webrtc::Transport {
public:
    RtcpTransport(const interface::RtpCapturerVideoSourceOptions& options);
    RtcpTransport(std::unique_ptr<network::interface::UdpClient> udp_client);
    ~RtcpTransport();

    // webrtc::Transport
    bool SendRtp(rtc::ArrayView<const uint8_t> packet,
                 const webrtc::PacketOptions& options) override;
    bool SendRtcp(rtc::ArrayView<const uint8_t> packet) override;

private:
    std::unique_ptr<network::interface::UdpClient> udp_client_ = nullptr;
};
// @endcond

}  // namespace rtp
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_RTP_RTCP_TRANSPORT_HPP_
