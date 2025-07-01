//
//  signaling_client.hpp
//  skyway
//
//  Created by sandabu on 2021/10/14.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_HPP_
#define SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_HPP_

#include <future>
#include <json.hpp>
#include <string>
#include <unordered_map>
#include <optional>

#include "skyway/signaling/dto/response.hpp"
#include "skyway/signaling/interface/member.hpp"
#include "skyway/signaling/interface/socket.hpp"

namespace skyway {
namespace signaling {
namespace interface {

/// @brief シグナリングサーバを介してメッセージを送るクライアント
class SignalingClient {
public:
    /// @brief イベントリスナ
    class Listener {
    public:
        virtual ~Listener() = default;
        virtual void OnConnectionFailed() {};

        /// @details srcのMemberのID, nameバリデーションを必ず行ってください。\n
        /// バリデーションを行うために実体で渡しています。
        virtual void OnRequestReceived(const nlohmann::json& data, const Member src) = 0;
        std::function<nlohmann::json(const nlohmann::json&, const std::string&, const std::string&)>
            reply;
    };
    /// @brief 応答デリデータ
    class Delegator {
    public:
        virtual ~Delegator() = default;
        /// @brief クライアントからリクエストが来たときの返信処理を行います。
        /// @param data リクエストデータ
        /// @param src リクエスタのクライアントID
        /// @param event_id リクエストのオーダーID
        /// @return レスポンスデータ
        virtual nlohmann::json reply(const nlohmann::json& data,
                                     const std::string& src,
                                     const std::string& event_id) {
            return nlohmann::json::object();
        };
    };
    struct Options {
        std::optional<int> connectivity_check_interval_sec;
        std::optional<std::string> signaling_domain;
        std::optional<bool> use_secure_protocol;
        bool operator==(const Options& rhs) const {
            if (connectivity_check_interval_sec == rhs.connectivity_check_interval_sec &&
                signaling_domain == rhs.signaling_domain &&
                use_secure_protocol == rhs.use_secure_protocol) {
                return true;
            }
            return false;
        }
    };
    virtual ~SignalingClient() = default;

    virtual void InterruptBlocking(const std::string& member_id) = 0;

    virtual void ResetBlocking(const std::string& member_id) = 0;

    /// @brief イベントリスナを設定します。
    /// @param listener リスナクラスのポインタ
    virtual void AddListener(Listener* listener) = 0;

    /// @brief イベントリスナを削除します。
    /// @param listener リスナクラスのポインタ
    virtual void RemoveListener(Listener* listener) = 0;
    /// @brief シグナリングサーバとの接続処理を行います。
    /// @details 接続後、サブスレッドにて死活監視の応答を行います。
    /// @param delegator 応答デリゲータのポインタ
    /// @param connectivity_check_interval_sec 死活監視の応答周期時間(秒)
    /// @return 正常処理完了かどうか
    virtual bool Connect(Delegator* delegator, int connectivity_check_interval_sec) = 0;

    /// @brief 対象のクライアントに対し、応答を必要とするメッセージを送信します。
    /// @details この関数を呼ぶ前にConnect関数を呼んでいる必要があります。
    /// @param target 対象のクライアントID
    /// @param data 送信するメッセージデータ
    /// @param timeout_sec タイムアウト秒
    /// @return 正常処理完了の場合、受信したJSONを含む構造体
    virtual signaling::dto::RequestResult Request(const Member& target,
                                                  const nlohmann::json& data,
                                                  const int timeout_sec,
                                                  const bool skip_response_wait = false) = 0;

    /// @brief 対象のクライアントに対し、応答を必要とするメッセージを送信します。
    /// @details この関数を呼ぶ前にConnect関数を呼んでいる必要があります。
    /// @param target 対象のクライアントID
    /// @param data 送信するメッセージデータ
    /// @return 正常処理完了の場合、受信したJSONを含む構造体
    virtual signaling::dto::RequestResult Request(const Member& target,
                                                  const nlohmann::json& data,
                                                  const bool skip_response_wait = false) = 0;
};

}  // namespace interface
}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_HPP_ */
