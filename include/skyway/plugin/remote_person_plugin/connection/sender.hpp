//
//  sender.hpp
//  skyway
//
//  Created by sandabu on 2021/11/10.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_SENDER_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_SENDER_HPP_

#include <api/media_stream_interface.h>
#include <api/peer_connection_interface.h>
#include <api/rtp_transceiver_interface.h>

#include <atomic>
#include <queue>
#include <unordered_map>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/ice_manager.hpp"
#include "skyway/core/interface/local_media_stream.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/stream/local/data_stream.hpp"
#include "skyway/model/domain.hpp"
#include "skyway/network/util.hpp"
#include "skyway/plugin/remote_person_plugin/connection/dto/message.hpp"
#include "skyway/plugin/remote_person_plugin/connection/peer.hpp"

namespace skyway {
namespace plugin {
namespace remote_person {
namespace connection {

/// @brief P2PにおいてStreamを送信するピア
class Sender : public Peer,
               public core::stream::local::LocalDataStream::InternalListener,
               public core::interface::Publication::InternalListener,
               public core::interface::Publication::Callback {
public:
    using SubscriptionId = std::string;

    /// コンストラクタ
    /// @param remote_member Messageパッケージ型のMember
    /// @param ice_manager IceManager
    /// @param messenger メッセンジャー
    /// @param peer_connection_factory PeerConnectionFactory
    /// @param analytics_client analyticsクライアント
    Sender(const MessageMember& remote_member,
           core::interface::IceManager* ice_manager,
           core::interface::ChunkMessenger* messenger,
           rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
           analytics::interface::AnalyticsClient* analytics_client);
    ~Sender();

    /// @brief ネゴシエーションを開始してStreamを送信します。
    /// @param publication Publication
    /// @param subscription_id SubscriptionのID
    bool Publish(core::interface::Publication* publication, const SubscriptionId& subscription_id);

    bool Unpublish(core::interface::Publication* publication);

    /// アンサーペイロードを処理します。
    /// @param payload アンサーペイロード
    bool HandleAnswerPayloadPayload(const dto::AnswerPayloadPayload& payload);

    bool ShouldClose();

    // core::stream::local::LocalDataStream::InternalListener
    void OnWriteData(const core::stream::local::LocalDataStream::SendingData& buffer,
                     const std::string& publication_id) override;

    // core::interface::Publication::Listener
    void OnEncodingsUpdated(core::interface::Publication* publication,
                            std::vector<model::Encoding> encodings) override;
    void OnStreamReplaced(core::interface::Publication* publication,
                          std::shared_ptr<core::interface::LocalMediaStream> stream) override;

    // core::interface::Publication::Callback
    const boost::optional<nlohmann::json> GetStatsReport(
        core::interface::Publication* publication) override;

protected:
    void OnConnectionChange(
        webrtc::PeerConnectionInterface::PeerConnectionState new_state) override;

private:
    webrtc::SessionDescriptionInterface* CreateOffer(bool ice_restart);
    bool SetLocalDescription(webrtc::SessionDescriptionInterface* desc);
    bool ApplyCodecCapabilities(std::vector<model::Codec> codec_caps,
                                const std::string& mid,
                                std::string& sdp);
    bool ApplyEncoding(const model::Encoding& encoding,
                       rtc::scoped_refptr<webrtc::RtpTransceiverInterface> transceiver);
    dto::SenderProduceMessage CreateProduceMessage(
        const std::string& publication_id,
        std::shared_ptr<core::interface::LocalStream> stream,
        const std::string& sdp,
        boost::optional<std::string> mid);

    rtc::scoped_refptr<webrtc::RtpTransceiverInterface> GetTransceiver(
        const std::string& publication_id);
    bool SetTransceiver(rtc::scoped_refptr<webrtc::RtpTransceiverInterface> transceiver,
                        const std::string& publication_id);
    bool RestartIce();

    void NotifyConnectionStateChanged(const core::ConnectionState new_state);
    void UpdateIceServers();
    void AddPublication(core::interface::Publication* publication);
    void RemovePublication(core::interface::Publication* publication);
    void RemoveFromPublication(core::interface::Publication* publication);
    void Reconnect(int max_ice_restart_count);

    using PublicationId = std::string;
    std::mutex transceivers_mutex_;
    std::unordered_map<PublicationId, rtc::scoped_refptr<webrtc::RtpTransceiverInterface>>
        transceivers_;
    std::mutex publications_mutex_;
    std::unordered_set<core::interface::Publication*> publications_;
    std::mutex restart_ice_threads_mtx;
    std::vector<std::unique_ptr<std::thread>> restart_ice_threads_;

    core::interface::IceManager* ice_manager_;
    std::atomic<core::ConnectionState> connection_state_;

public:
    friend class P2PConnectionTest;
    friend class RemotePersonPluginSenderTest;
};

}  // namespace connection
}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_SENDER_HPP_ */
