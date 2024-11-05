//
//  socket.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2022/10/07.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_INTERFACE_SOCKET_HPP_
#define SKYWAY_SIGNALING_INTERFACE_SOCKET_HPP_

#include "skyway/signaling/client_event.hpp"

namespace skyway {
namespace signaling {
namespace interface {

/// SignalingにおけるWebSocketクライアント
class Socket {
public:
    class Listener {
    public:
        virtual void OnConnectionFailed()                       = 0;
        virtual void OnDataReceived(const nlohmann::json& data) = 0;
    };
    virtual ~Socket() = default;
    /// @brief リスナーを登録します。
    /// @details リスナーの登録解除は`Dispose`をコールしてください。
    virtual void RegisterListener(Listener* listener) = 0;
    /// @brief シグナリングサーバに接続します。
    /// @details 接続失敗した場合、設定回数に応じて再試行します。
    virtual bool Connect() = 0;

    /// @brief イベントを送信します。
    /// @param event イベント
    virtual bool Send(const ClientEvent& event) = 0;

    /// @brief ソケットがオープン状態か返します。
    /// @details
    /// WebSocketオブジェクトの状態ではなく、シグナリングサーバが管理しているopen状態であることに注意してください。
    virtual bool IsOpen() = 0;

    /// @brief WebSocketを切断し、リスナーが完了するまで待機します。
    virtual void Dispose() = 0;
};

}  // namespace interface
}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_INTERFACE_SOCKET_HPP_ */
