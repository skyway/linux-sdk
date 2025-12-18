//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CHUNK_MESSENGER_CHUNK_MESSENGER_HPP_
#define SKYWAY_CORE_CHUNK_MESSENGER_CHUNK_MESSENGER_HPP_

#include <json.hpp>
#include <unordered_map>
#include <unordered_set>

#include "skyway/core/interface/chunk_messenger.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"

namespace skyway {
namespace core {
namespace chunk_messenger {

using ChunkMessengerInterface  = interface::ChunkMessenger;
using SignalingClientListener  = signaling::interface::SignalingClient::Listener;
using SignalingClientDelegator = signaling::interface::SignalingClient::Delegator;

class ChunkMessenger : public ChunkMessengerInterface,
                       public SignalingClientListener,
                       public SignalingClientDelegator {
public:
    using SignalingClientInterface = signaling::interface::SignalingClient;
    using RequestId                = std::string;
    using ChunkedMessage           = std::string;
    /// @brief コンストラクタ
    /// @param client ChunkMessengerインターフェース
    ChunkMessenger(std::unique_ptr<SignalingClientInterface> client);
    ~ChunkMessenger();

    void AddListener(const signaling::interface::Member& remote_member,
                     ChunkMessengerInterface::Listener* listener) override;
    void RemoveListener(const signaling::interface::Member& remote_member) override;

    bool Connect(int connectivity_check_interval_sec) override;

    dto::SendResult Send(const signaling::interface::Member& target_member,
                         const nlohmann::json& message,
                         const bool skip_response_wait) override;
    void ResolveBufferedMessages(const signaling::interface::Member& src) override;

    void OnRequestReceived(const nlohmann::json& data,
                           const signaling::interface::Member src) override;
    void OnConnectionFailed() override;

    void ResetBlocking(const std::string& member_id) override;

    void InterruptBlocking(const std::string& member_id) override;

private:
    using MemberId                  = std::string;
    using ListenerValueTuple        = std::tuple<signaling::interface::Member,
                                                 ChunkMessengerInterface::Listener*,
                                                 std::vector<std::unique_ptr<std::thread>>>;
    using BufferedMessagesValuePair = std::pair<signaling::interface::Member, nlohmann::json>;

    void EmitEvent(const nlohmann::json& message,
                   const signaling::interface::Member& src,
                   ListenerValueTuple& tuple);

    std::mutex listeners_mtx_;
    std::unordered_map<MemberId, ListenerValueTuple> listeners_;
    std::unordered_map<RequestId, std::vector<ChunkedMessage>> signaling_buffer_;
    std::unordered_multimap<MemberId, BufferedMessagesValuePair> buffered_messages_;

    std::unique_ptr<SignalingClientInterface> signaling_client_;

    std::mutex request_received_threads_mtx_;
    std::vector<std::unique_ptr<std::thread>> request_received_threads_;
};

}  // namespace chunk_messenger
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CHUNK_MESSENGER_CHUNK_MESSENGER_HPP_ */
