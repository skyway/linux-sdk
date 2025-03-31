//
//  receiver.hpp
//  skyway
//
//  Created by sandabu on 2021/11/16.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_RECEIVER_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_RECEIVER_HPP_

#include <api/media_stream_interface.h>
#include <api/peer_connection_interface.h>
#include <api/rtp_transceiver_interface.h>

#include <atomic>
#include <queue>
#include <unordered_map>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/ice_manager.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/core/stream/remote/data_stream.hpp"
#include "skyway/plugin/remote_person_plugin/connection/dto/message.hpp"
#include "skyway/plugin/remote_person_plugin/connection/peer.hpp"

namespace skyway {
namespace plugin {
namespace remote_person {
namespace connection {

/// @brief P2PにおいてStreamを受信するピア
class Receiver : public Peer,
                 public Peer::Listener,
                 public core::interface::Subscription::Callback {
public:
    /// コンストラクタ
    /// @param remote_member Messageパッケージ型のMember
    /// @param ice_manager IceManager
    /// @param messenger シグナラ
    /// @param peer_connection_factory PeerConnectionFactory
    /// @param analytics_client analyticsクライアント
    Receiver(const MessageMember& remote_member,
             core::interface::IceManager* ice_manager,
             core::interface::ChunkMessenger* messenger,
             rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
             analytics::interface::AnalyticsClient* analytics_client);
    ~Receiver();

    /// @brief ネゴシエーションを開始してStreamを受信します。
    /// @param subscription Subscription
    bool Subscribe(std::shared_ptr<core::interface::Subscription> subscription);

    bool Unsubscribe(const std::string& subscription_id);

    /// オファーペイロードを処理します。
    /// @param payload オファーペイロード
    bool HandleProducePayloadPayload(const dto::ProducePayloadPayload& payload);

    bool HandleUnproducePayloadPayload(const dto::UnproducePayloadPayload& payload);

    bool HandleRestartIcePayloadPayload(const dto::RestartIcePayloadPayload& payload);

    bool ShouldClose();

    // Impl Peer Listener
    void OnConnect(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel,
                   const DataChannelLabel& label) override;
    void OnMessage(const webrtc::DataBuffer& buffer, const DataChannelLabel& label) override;

    // Impl core::interface::Subscription::Callback
    const std::optional<nlohmann::json> GetStatsReport(
        std::shared_ptr<core::interface::Subscription> subscription) override;

protected:
    // Impl `webrtc::PeerConnectionObserver`
    void OnConnectionChange(
        webrtc::PeerConnectionInterface::PeerConnectionState new_state) override;

    // webrtc::PeerConnectionObserver
    // It is called during `SetRemoteDescription()`
    void OnTrack(rtc::scoped_refptr<webrtc::RtpTransceiverInterface> transceiver) override;

private:
    bool Answer(const std::string& remote_sdp);
    void SetupTransportAccessForStream();
    bool IsInvalidSignalingState();
    void NotifyConnectionStateChanged(const core::ConnectionState new_state);

    std::weak_ptr<core::interface::Subscription> target_subscription_;
    std::mutex subscriptions_mutex_;
    std::vector<std::weak_ptr<core::interface::Subscription>> subscriptions_;
    std::mutex publication_info_mutex_;
    std::vector<dto::ProducePayloadPayloadInfo> publication_info_;
    std::atomic<core::ConnectionState> connection_state_;

public:
    friend class RemotePersonPluginReceiverTest;
};

}  // namespace connection
}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_RECEIVER_HPP_ */
