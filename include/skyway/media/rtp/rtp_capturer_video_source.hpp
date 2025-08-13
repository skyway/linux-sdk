//
//  rtp_capturer_video_source.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2025/06/30.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_RTP_RTP_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_RTP_RTP_CAPTURER_VIDEO_SOURCE_HPP_

#include <api/field_trials.h>
#include <video/rtp_video_stream_receiver2.h>

#include "skyway/global/worker.hpp"
#include "skyway/media/codec/video_codec.hpp"
#include "skyway/media/i420_capturer_video_source.hpp"
#include "skyway/media/rtp/interface/rtp_capturer_video_source.hpp"
#include "skyway/media/rtp/interface/rtp_capturer_video_source_repository.hpp"
#include "skyway/network/interface/udp_server.hpp"

namespace skyway {
namespace media {
namespace rtp {
/// @cond INTERNAL_SECTION
class FakeTransport : public webrtc::Transport {
public:
    bool SendRtp(rtc::ArrayView<const uint8_t> packet,
                 const webrtc::PacketOptions& options) override {
        return true;
    }

    bool SendRtcp(rtc::ArrayView<const uint8_t> packet) override { return true; }
};
// @endcond

class RtpCapturerVideoSource : public interface::RtpCapturerVideoSource,
                               public network::interface::UdpServer::PacketHandler,
                               public webrtc::RtpVideoStreamReceiver2::OnCompleteFrameCallback,
                               public std::enable_shared_from_this<RtpCapturerVideoSource> {
public:
    /// @cond INTERNAL_SECTION
    RtpCapturerVideoSource(const interface::RtpCapturerVideoSourceOptions& options,
                           std::shared_ptr<codec::VideoCodec> codec,
                           std::unique_ptr<network::interface::UdpServer> udp_server,
                           std::shared_ptr<interface::RtpCapturerVideoSourceRepository> repository,
                           std::unique_ptr<rtc::Thread> depacketize_th);
    ~RtpCapturerVideoSource();
    /// @endcond

    /**
     * @brief RTPキャプチャビデオソースのインスタンスを作成します。
     * @details
     * 生成はこちらのメソッドをコールしてください。
     *
     * この機能を利用するためには`Context::Setup`におけるSkyWayOptionsのRtp::Input::Videoにおいて、`enabled`を`true`に設定し、`codec`に適切なコーデックを設定する必要があります。
     *
     * 設定されていない場合、nullptrを返します。
     * @param options オプション
     * @return std::shared_ptr<RtpCapturerVideoSource>
     */
    static std::shared_ptr<RtpCapturerVideoSource> Create(
        const interface::RtpCapturerVideoSourceOptions& options);

    bool StartReceiving() override;
    bool StopReceiving() override;

    /// @cond INTERNAL_SECTION
    std::optional<uint8_t> GetFrameId() override;
    void RegisterCallback(webrtc::EncodedImageCallback* callback) override;
    std::string Endpoint() const override;
    void OnEncoderReleased(webrtc::EncodedImageCallback* callback) override;
    rtc::scoped_refptr<media::interface::InternalCapturerVideoSource> GetSource() override;
    // Impl network::interface::UdpServer::PacketHandler
    void OnPacketReceived(const uint8_t* data, size_t size) override;
    // Impl webrtc::RtpVideoStreamReceiver2::OnCompleteFrameCallback
    void OnCompleteFrame(std::unique_ptr<webrtc::EncodedFrame> frame) override;
    /// @endcond
private:
    RtpCapturerVideoSource(const interface::RtpCapturerVideoSourceOptions& options);
    std::unique_ptr<webrtc::RtpVideoStreamReceiver2> CreateReceiver(
        const webrtc::RtpPacketReceived& packet);
    void DummyFrameLoop(uint16_t frame_id);
    uint64_t GenerateSsrc() const;
    webrtc::VideoReceiveStreamInterface::Config CreateFakeConfig() const;

    std::shared_ptr<codec::VideoCodec> codec_;
    std::unique_ptr<rtc::Thread> depacketize_th_ = nullptr;
    FakeTransport transport_;
    interface::RtpCapturerVideoSourceOptions options_;
    rtc::scoped_refptr<I420CapturerVideoSource::I420InternalCapturerVideoSource> source_;
    std::unique_ptr<network::interface::UdpServer> udp_server_;
    std::mutex callbacks_mtx_;
    std::unordered_set<webrtc::EncodedImageCallback*> callbacks_;
    std::unique_ptr<webrtc::FieldTrials> trials_ = nullptr;
    webrtc::VideoReceiveStreamInterface::Config config_;
    std::unique_ptr<webrtc::TaskQueueBase, webrtc::TaskQueueDeleter> encoded_image_queue_ = nullptr;
    std::unique_ptr<webrtc::RtpVideoStreamReceiver2> receiver_                            = nullptr;
    std::atomic<bool> frame_loop_stopped_                                                 = true;
    global::Worker dummy_frame_worker_;
    std::optional<uint16_t> frame_id_;
    std::atomic<bool> is_receiving = false;
    std::weak_ptr<interface::RtpCapturerVideoSourceRepository> repo_;

public:
    /// @cond INTERNAL_SECTION
    friend class RtpCapturerVideoSourceTest;
    /// @endcond
};

}  // namespace rtp
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_RTP_RTP_CAPTURER_VIDEO_SOURCE_HPP_ */
