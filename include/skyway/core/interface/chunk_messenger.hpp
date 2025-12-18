//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_HPP_
#define SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_HPP_

#include <json.hpp>

#include "skyway/core/chunk_messenger/dto/message.hpp"
#include "skyway/network/interface/websocket_client.hpp"
#include "skyway/signaling/interface/member.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"
#include "skyway/signaling/interface/socket.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace core {
namespace interface {

/// @brief RemoteMemberとチャンキングされたメッセージを送受信するインターフェース
class ChunkMessenger {
public:
    using WebSocketClientInterface  = network::interface::WebSocketClient;
    using SingnalingClientInterface = signaling::interface::SignalingClient;
    using SocketInterface           = signaling::interface::Socket;

    /// イベントリスナ
    class Listener {
    public:
        /// @brief メッセージ受信イベント
        ///
        /// @details
        /// 新しくスレッドを作成して通知します。メッセージが連続してきた場合は順に同期処理されます。
        /// @param message メッセージ
        virtual void OnMessage(const nlohmann::json& message) = 0;
    };
    virtual void ResetBlocking(const std::string& member_id) = 0;
    virtual void InterruptBlocking(const std::string& member_id) = 0;
    virtual ~ChunkMessenger() = default;
    /// @brief リスナーを追加します。
    /// @param remote_member 登録対象のRemoteMember
    /// @param listener リスナー
    virtual void AddListener(const signaling::interface::Member& remote_member,
                             Listener* listener) = 0;
    /// @brief リスナーを削除します。
    /// @param remote_member 登録解除対象のRemoteMember
    virtual void RemoveListener(const signaling::interface::Member& remote_member) = 0;
    /// @brief シグナリングサーバとの接続処理を行います。
    /// @param connectivity_check_interval_sec 接続チェックインターバル時間
    virtual bool Connect(int connectivity_check_interval_sec) = 0;

    /// @brief 対象のクライアントに対し、RTCメッセージを送信します。
    /// @details この関数を呼ぶ前にConnect関数を呼んでいる必要があります。
    /// @param target_member 送信先のMember
    /// @param data 送信するメッセージ
    virtual chunk_messenger::dto::SendResult Send(const signaling::interface::Member& target_member,
                                                  const nlohmann::json& data,
                                                  const bool skip_response_wait = false) = 0;

    /// @brief リスナー登録までバッファリングしていたメッセージをリスナーに発火させます。
    ///
    /// @details この関数をコールする前に`AddListener`をコールする必要があります。
    ///
    /// 新しくスレッドを作成して`Listener::OnMessage`をコールしますが、複数バッファされている場合は順に同期処理されます。
    /// @param sender メッセージの送信者(RemoteMember)
    virtual void ResolveBufferedMessages(const signaling::interface::Member& sender) = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_HPP_ */
