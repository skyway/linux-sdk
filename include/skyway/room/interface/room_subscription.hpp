//
//  room_subscription.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/11/21.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_SUBSCRIPTION_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_SUBSCRIPTION_HPP

#include <skyway/core/interface/subscription.hpp>

#include "skyway/room/interface/room_member.hpp"

namespace skyway {
namespace room {
namespace interface {

class RoomPublication;

/// @brief RoomのSubscriptionを操作するインタフェース
class RoomSubscription {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        virtual ~EventListener() = default;
        /// @deprecated 本機能は非推奨です。
        /// @brief Subscribeが中止(unsubscribe)された後に発生するイベント
        [[deprecated]] virtual void OnCanceled() {}

        /// @brief Subscribe中のStream接続状態が変更された後に発生するイベント
        /// @param state 接続状態
        virtual void OnConnectionStateChanged(const core::ConnectionState state) {}
    };
    virtual ~RoomSubscription() = default;
    /// @brief Idを取得します。
    virtual std::string Id() = 0;
    /// @brief ContentType(VideoかAudioかDataか)を取得します。
    virtual model::ContentType ContentType() = 0;
    /// @brief このSubscriptionに紐づくPublicationを取得します。
    virtual std::shared_ptr<RoomPublication> Publication() = 0;
    /// @brief このSubscriptionを購読しているMemberを取得します。
    virtual std::shared_ptr<RoomMember> Subscriber() = 0;
    /// @brief State(公開状態がEnableかDisabelかCancelか)を取得します。
    virtual core::interface::SubscriptionState State() = 0;
    /// @brief Publisherが持つStreamを取得します。
    virtual std::shared_ptr<core::interface::RemoteStream> Stream() = 0;
    /// @brief このSubscriptionの優先エンコーディングIDを取得します。
    virtual std::optional<std::string> PreferredEncodingId() = 0;

    /// @brief イベントを購読します。
    virtual void AddEventListener(EventListener* listener) = 0;
    /// @brief イベントの購読を中止します。
    virtual void RemoveEventListener(EventListener* listener) = 0;
    /// @brief 受信するエンコード設定を切り替えます。
    virtual bool ChangePreferredEncoding(const std::string& id) = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief Subscribeを中止します。
    [[deprecated]] virtual bool Cancel() = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief 統計情報を取得します。
    /// @details 試験的なAPIです。今後インターフェースや仕様が変更される可能性があります。
    [[deprecated]] virtual std::optional<model::WebRTCStats> GetStats() = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_SUBSCRIPTION_HPP */
