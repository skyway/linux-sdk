//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ANALYTICS_INTERFACE_SOCKET_HPP_
#define SKYWAY_ANALYTICS_INTERFACE_SOCKET_HPP_

#include <json.hpp>

#include "skyway/analytics/client_event.hpp"
#include "skyway/analytics/server_event.hpp"

namespace skyway {
namespace analytics {
namespace interface {

/// AnalyticsにおけるWebSocketクライアント
class Socket {
public:
    class Listener {
    public:
        virtual void OnConnectionFailed()               = 0;
        virtual void OnOpen(const OpenPayload& payload) = 0;
    };
    virtual ~Socket() = default;
    /// @brief リスナーを登録します。
    /// @details リスナーの登録解除は`Dispose`をコールしてください。
    virtual void RegisterListener(Listener* listener) = 0;
    /// @brief アナリティクスサーバに接続します。
    /// @details 接続失敗した場合、設定回数に応じて再試行します。
    virtual bool Connect() = 0;

    /// @brief イベントを送信します。
    /// @param event イベント
    virtual bool Send(const ClientEvent& event) = 0;

    /// @brief ソケットがオープン状態か返します。
    /// @details
    /// WebSocketオブジェクトの状態ではなく、アナリティクスサーバが管理しているopen状態であることに注意してください。
    virtual bool IsOpen() const = 0;

    /// @brief WebSocketを切断し、リスナーが完了するまで待機します。
    virtual void Dispose() = 0;
};

}  // namespace interface
}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_INTERFACE_SOCKET_HPP_ */
