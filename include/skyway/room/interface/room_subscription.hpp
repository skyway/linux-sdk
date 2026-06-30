//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_SUBSCRIPTION_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_SUBSCRIPTION_HPP

#include "skyway/domain/domain.hpp"
#include "skyway/room/interface/room_member.hpp"
#include "skyway/room/types.hpp"

#include "skyway/media/stream/interface/remote/remote_stream.hpp"

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
        /// @brief Subscribe中のStream接続状態が変更された後に発生するイベント
        /// @param state 接続状態
        virtual void OnConnectionStateChanged(const ConnectionState state) {}

        /// @brief SubscriptionのRemoteStreamが利用可能になった後に発生するイベント
        /// @param stream RemoteStream
        virtual void OnStreamAttached(
            std::shared_ptr<media::stream::interface::remote::RemoteStream> stream) {}
    };
    virtual ~RoomSubscription() = default;
    /// @brief Idを取得します。
    virtual std::string Id() = 0;
    /// @brief ContentType(VideoかAudioかDataか)を取得します。
    virtual domain::ContentType ContentType() = 0;
    /// @brief このSubscriptionに紐づくPublicationを取得します。
    virtual std::shared_ptr<RoomPublication> Publication() = 0;
    /// @brief このSubscriptionを購読しているMemberを取得します。
    virtual std::shared_ptr<RoomMember> Subscriber() = 0;
    /// @brief State(公開状態がEnableかDisabelかCancelか)を取得します。
    virtual SubscriptionState State() = 0;
    /// @brief Publisherが持つStreamを取得します。
    virtual std::shared_ptr<media::stream::interface::remote::RemoteStream> Stream() = 0;
    /// @brief このSubscriptionの優先エンコーディングIDを取得します。
    virtual std::optional<std::string> PreferredEncodingId() = 0;

    /// @brief イベントを購読します。
    virtual void AddEventListener(EventListener* listener) = 0;
    /// @brief イベントの購読を中止します。
    virtual void RemoveEventListener(EventListener* listener) = 0;
    /// @brief 受信するエンコード設定を切り替えます。
    virtual bool ChangePreferredEncoding(const std::string& id) = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief 統計情報を取得します。
    /// @details 試験的なAPIです。今後インターフェースや仕様が変更される可能性があります。
    [[deprecated]] virtual std::optional<WebRTCStats> GetStats() = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_SUBSCRIPTION_HPP */
