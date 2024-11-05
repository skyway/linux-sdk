//
//  subscription.hpp
//  skyway
//
//  Created by sandabu on 2022/01/13.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_SUBSCRIPTION_HPP_
#define SKYWAY_CORE_INTERFACE_SUBSCRIPTION_HPP_

#include "skyway/core/connection_state.hpp"
#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/remote_stream.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class Publication;

/// @brief Subscriptionの状態
enum class SubscriptionState { kEnabled, kDisabled, kCanceled };

/// @brief Subscriptionのインターフェース
class Subscription : public ConnectionStateChangeNotifiable {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        /// @deprecated 本機能は非推奨です。
        /// @brief このSubscriptionのSubscribeがキャンセルされた際に発火するイベント。
        [[deprecated]] virtual void OnCanceled() {}
        /// @brief このSubscriptionの通信が有効になった時に発火するイベント。
        /// Publication.Enableが実行された時に発火します。
        virtual void OnEnabled() {}
        /// @brief このSubscriptionの通信が無効になった時に発火するイベント。
        /// Publication.Disableが実行された時に発火します。
        virtual void OnDisabled() {}
        /// @brief このSubscriptionのメディア通信の状態が変化した時に発火するイベント
        virtual void OnConnectionStateChanged(const ConnectionState state) {}
    };
    /// @cond INTERNAL_SECTION
    class InternalListener {
    public:
        virtual void OnChangePreferredEncoding(Subscription* subscription) = 0;
    };
    class Callback {
    public:
        virtual const boost::optional<nlohmann::json> GetStatsReport(
            Subscription* subscription) = 0;
    };
    /// @endcond
    virtual ~Subscription() = default;

    /// @brief イベントを購読します。
    /// @param listener イベントリスナ
    virtual void AddEventListener(EventListener* listener) = 0;
    /// @brief イベントの購読を中止します。
    /// @param listener 対象のイベントリスナ
    virtual void RemoveEventListener(EventListener* listener) = 0;
    /// @cond INTERNAL_SECTION
    virtual void AddInternalListener(InternalListener* listener)    = 0;
    virtual void RemoveInternalListener(InternalListener* listener) = 0;
    /// @endcond

    /// @brief Idを取得します。
    virtual std::string Id() const = 0;
    /// @brief ContentType(VideoかAudioかDataか)を取得します。
    virtual model::ContentType ContentType() const = 0;
    /// @brief このSubscriptionに紐づくPublicationを取得します。
    virtual Publication* Publication() const = 0;
    /// @brief このSubscriptionをSubscribeしているMemberを取得します。
    virtual Member* Subscriber() const = 0;
    /// @brief State(公開状態がEnableかDisabelかCancelか)を取得します。
    virtual SubscriptionState State() = 0;
    /// @brief Publisherが持つStreamを取得します。
    /// @details
    /// `LocalPerson.subscribe`の返り値でSubscriptionを入手した場合、入手時点で値がsetされています。
    /// その他、イベントの発火によってSubscriptionを取得した場合、まだ値がsetされていない可能性があります。
    virtual std::shared_ptr<RemoteStream> Stream() = 0;
    /// @brief このSubscriptionの優先エンコーディングIDを取得します。
    virtual boost::optional<std::string> PreferredEncodingId() const = 0;
    /// @brief 受信するエンコード設定を切り替えます。
    virtual void ChangePreferredEncoding(const std::string& id) = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief Subscribeを中止します。
    [[deprecated]] virtual bool Cancel() const = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief 統計情報を取得します。
    [[deprecated]] virtual boost::optional<model::WebRTCStats> GetStats() = 0;
    /// @cond INTERNAL_SECTION
    /// @brief Subscriptionの購読を開始します。disableによって停止していた場合は再開します。
    virtual bool Enable() const = 0;
    /// @brief Subscriptionの購読を一時停止します。
    virtual bool Disable() const                         = 0;
    virtual void AddGetStatsCallback(Callback* callback) = 0;
    virtual void RemoveGetStatsCallback()                = 0;

    virtual void SetStream(std::shared_ptr<RemoteStream> stream) = 0;
    virtual void SetPreferredEncodingId(const std::string& id)   = 0;

    virtual void OnCanceled() = 0;
    virtual void OnEnabled()  = 0;
    virtual void OnDisabled() = 0;
    /// @endcond
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_SUBSCRIPTION_HPP_ */
