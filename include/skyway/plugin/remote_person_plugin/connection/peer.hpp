//
//  peer.hpp
//  skyway
//
//  Created by sandabu on 2021/11/16.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_PEER_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_PEER_HPP_

#include <api/data_channel_interface.h>
#include <api/media_stream_interface.h>
#include <api/peer_connection_interface.h>

#include <queue>
#include <unordered_map>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/chunk_messenger.hpp"
#include "skyway/core/interface/ice_manager.hpp"
#include "skyway/plugin/remote_person_plugin/connection/data_channel_label.hpp"
#include "skyway/plugin/remote_person_plugin/connection/dto/message.hpp"
#include "skyway/signaling/interface/member.hpp"
#include "skyway/global/worker.hpp"

namespace skyway {
namespace plugin {
namespace remote_person {
namespace connection {

using MessageMember           = signaling::interface::Member;
using ChunkMessengerInterface = core::interface::ChunkMessenger;

const std::string kRemotePersonConnectionStateThreadName = "remo_psn_conn";

/// P2Pを行う抽象的なピア
class Peer : public webrtc::PeerConnectionObserver {
public:
    enum Role { kSender, kReceiver };

    class Listener {
    public:
        virtual ~Listener() = default;
        virtual void OnConnect(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel,
                               const DataChannelLabel& label) {}
        virtual void OnMessage(const webrtc::DataBuffer& buffer, const DataChannelLabel& label) {}
    };

    // Observers related with PeerConnection
    class CreateSdpObserver : public webrtc::CreateSessionDescriptionObserver {
    public:
        CreateSdpObserver();
        webrtc::SessionDescriptionInterface* WaitForResult();
        // webrtc::CreateSessionDescriptionObserver
        void OnSuccess(webrtc::SessionDescriptionInterface* desc) override;
        void OnFailure(webrtc::RTCError error) override;

    private:
        webrtc::SessionDescriptionInterface* desc_;
        std::atomic<bool> finished_;

        std::mutex mtx_;
    };

    class SetSdpObserver : public webrtc::SetSessionDescriptionObserver {
    public:
        SetSdpObserver();
        bool WaitForResult();
        // webrtc::SetSessionDescriptionObserver
        void OnSuccess() override;
        void OnFailure(webrtc::RTCError error) override;

    private:
        std::atomic<bool> finished_;
        std::atomic<bool> result_;

        std::mutex mtx_;
    };

    class DataChannelObserver : public webrtc::DataChannelObserver {
    public:
        DataChannelObserver(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel,
                            Listener* listener,
                            Role role);
        ~DataChannelObserver();
        // webrtc::DataChannelObserver
        void OnStateChange() override;
        void OnMessage(const webrtc::DataBuffer& buffer) override;
        rtc::scoped_refptr<webrtc::DataChannelInterface> GetDataChannel();
        std::optional<DataChannelLabel> GetParsedLabel();

    private:
        Listener* listener_;
        Role role_;
        rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel_;
    };

    class StatsObserver : public webrtc::RTCStatsCollectorCallback {
    public:
        rtc::scoped_refptr<const webrtc::RTCStatsReport> WaitForResult();
        void OnStatsDelivered(
            const rtc::scoped_refptr<const webrtc::RTCStatsReport>& report) override;

    private:
        rtc::scoped_refptr<const webrtc::RTCStatsReport> report_;
        std::atomic<bool> finished_;
        std::mutex mtx_;
    };

    Peer(Role role,
         const MessageMember& remote_member,
         core::interface::IceManager* ice_manager,
         ChunkMessengerInterface* messenger,
         Listener* listener,
         rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
         analytics::interface::AnalyticsClient* analytics_client);
    virtual ~Peer();
    /// データチャネルが送信可能なオープン状態かどうか返します。
    /// @param publication_id Publication ID
    bool IsDataChannelOpen(const std::string& publication_id);

    /// データチャネルを利用してメッセージを送信します。
    /// @param data データ
    /// @param size データサイズ
    /// @param is_binary バイナリかどうか
    /// @param publication_id Publication ID
    /// @return 処理成功かどうか
    bool SendMessage(const uint8_t* data,
                     std::size_t size,
                     bool is_binary,
                     const std::string& publication_id);
    void HandleCandidate(const dto::IceCandidate& candidate);

    bool disconnected_;

    void Dispose();

protected:
    dto::SendResult SendMessage(const nlohmann::json& message, const bool skip_response_wait = false);
    void ResolvePendingCandidates();

    rtc::scoped_refptr<webrtc::DataChannelInterface> GetDataChannel(
        const std::string& publication_id);
    bool SetDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel);

    bool RemoveDataChannel(const std::string& publication_id);

    bool AnyDataChannels();

    bool WaitForSignalingState(webrtc::PeerConnectionInterface::SignalingState state);

    // webrtc::PeerConnectionObserver
    void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state) override;

    void OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel) override;

    void OnRenegotiationNeeded() override;

    void OnIceConnectionChange(
        webrtc::PeerConnectionInterface::IceConnectionState new_state) override;

    void OnStandardizedIceConnectionChange(
        webrtc::PeerConnectionInterface::IceConnectionState new_state) override;

    void OnConnectionChange(
        webrtc::PeerConnectionInterface::PeerConnectionState new_state) override;

    void OnIceGatheringChange(
        webrtc::PeerConnectionInterface::IceGatheringState new_state) override;

    void OnIceCandidate(const webrtc::IceCandidateInterface* candidate) override;

    void OnIceCandidateError(const std::string& address,
                             int port,
                             const std::string& url,
                             int error_code,
                             const std::string& error_text) override;

    rtc::scoped_refptr<webrtc::PeerConnectionInterface> pc_;
    rtc::scoped_refptr<CreateSdpObserver> create_sdp_observer_;
    rtc::scoped_refptr<SetSdpObserver> set_sdp_observer_;
    rtc::scoped_refptr<StatsObserver> stats_observer_;
    MessageMember remote_member_;
    ChunkMessengerInterface* messenger_;

    analytics::interface::AnalyticsClient* analytics_client_;

    std::mutex negotiation_mtx_;

    std::string rtc_peer_connection_id_;
    std::unique_ptr<global::interface::Worker> connection_state_worker_ = std::make_unique<global::Worker>(kRemotePersonConnectionStateThreadName);
    std::atomic<bool> is_disposed_ = false;

private:
    bool SendCandidate(const webrtc::IceCandidateInterface* candidate);
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> CreatePeerConnection(
        webrtc::PeerConnectionInterface::RTCConfiguration& config,
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory);
    std::string GetRoleName();

    Role role_;

    Listener* listener_;
    std::mutex data_channel_observers_mtx_;
    std::vector<std::unique_ptr<DataChannelObserver>> data_channel_observers_;

    std::mutex pending_remote_candidates_mtx_;
    std::vector<dto::IceCandidate> pending_remote_candidates_;
    // for unit test
    std::vector<dto::CandidatePayloadPayload> candidates_;

public:
    friend class P2PConnectionTest;
};

}  // namespace connection
}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_CONNECTION_PEER_HPP_ */
