//
//  websocket_client.hpp
//  skyway
//
//  Created by sandabu on 2021/11/09.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_WEBSOCKET_CLIENT_HPP_
#define SKYWAY_NETWORK_INTERFACE_WEBSOCKET_CLIENT_HPP_

#include <future>
#include <memory>
#include <unordered_map>
#include <vector>

namespace skyway {
namespace network {
namespace interface {

/// @brief WebSocketクライアント
///
/// @details Platformにてこのインターフェースを実装して、Context::Setupに渡してください。
class WebSocketClient {
public:
    /// イベントリスナー
    class Listener {
    public:
        /// @brief メッセージを受信した時にコールされます。
        /// @details
        /// この関数はlibskyway内部で重い同期処理をする可能性があるため、PFではサブスレッドからコールしてください。
        /// @param message 受信したメッセージ
        virtual void OnMessage(const std::string& message) = 0;
        /// @brief WebSocketが閉じた時にコールされます。
        /// @details
        /// この関数はlibskyway内部で重い同期処理をする可能性があるため、PFではサブスレッドからコールしてください。
        /// @param code Closeコード
        virtual void OnClose(const int code, const std::string& reason) {}
        /// @brief WebSocketサーバからエラーが返ってきた時にコールされます。
        /// @param code Responseステータスコード
        virtual void OnError(const int code) {}
    };

    /// @brief デストラクタ
    /// @details 接続中の場合はCloseしてから破棄するように実装してください。
    virtual ~WebSocketClient() = default;

    /// @brief イベントリスナーを登録します
    /// @param listener イベントリスナー
    virtual void RegisterListener(Listener* listener) = 0;

    /// @brief WebSocketサーバに接続します。
    /// @param url サーバエンドポイントURL
    /// @param sub_protocols サブプロトコル
    /// @param headers リクエストヘッダー
    virtual std::future<bool> Connect(
        const std::string& url,
        const std::vector<std::string>& sub_protocols,
        const std::unordered_map<std::string, std::string>& headers) = 0;

    /// @brief メッセージを送信します。
    /// @details このAPIをコールする前に`Connect(url, sub_protocol)`をコールしてください。
    virtual std::future<bool> Send(const std::string& message) = 0;

    /// @brief WebSocketクライアントをCloseします。
    /// @param code Closeコード
    /// @param reason Close理由
    virtual std::future<bool> Close(const int code, const std::string& reason) = 0;

    /// @brief WebSocketクライアントをCloseします。
    /// @param code Closeコード
    std::future<bool> Close(const int code);

    /// @brief WebSocketクライアントを正常コード(1000)にてCloseします。
    std::future<bool> Close();

    /// @brief WebSocketクライアントを破棄します。
    /// @details
    /// WebSocketクライアントを所有しているクラスは必ずデストラクタでこのAPIをコールしてください。
    ///
    /// 安全にメモリを破棄するために内部ではリスナー実行スレッド完了まで待ちます。
    virtual std::future<bool> Destroy() = 0;
};

/// @brief PFで実装したWebSocketClientを生成するファクトリークラス
///
/// @details `Context.Setup()`にインジェクションします。
class WebSocketClientFactory {
public:
    virtual ~WebSocketClientFactory()                 = default;
    virtual std::shared_ptr<WebSocketClient> Create() = 0;
    /// @brief WebSocketFactoryをセットします。
    /// @details `Context::Setup()`内でセットします。
    /// @param factory WebSocketFactory
    static void SetSharedInstance(std::unique_ptr<WebSocketClientFactory> factory);

    /// @brief WebSocketFactoryのポインタを取得します。
    static WebSocketClientFactory* Shared();

private:
    static std::unique_ptr<WebSocketClientFactory> shared_;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif /* SKYWAY_NETWORK_INTERFACE_WEBSOCKET_CLIENT_HPP_ */
