//
//  subscription.hpp
//  skyway
//
//  Created by sandabu on 2022/01/13.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
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
// `std::enable_shared_from_this<T>` is supposed to be inherited by concrete classes.
// (e.g. skyway/core/subscription.hpp)
// however if so, compile failed on the Android SDK that includes interfaces.
class Subscription : public std::enable_shared_from_this<Subscription>,
                     public ConnectionStateChangeNotifiable {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        /// @deprecated 本機能は非推奨です。
        /// @brief このSubscriptionのSubscribeがキャンセルされた際に発火するイベント。
        [[deprecated]] virtual void OnCanceled() {}
        /// @brief このSubscriptionのメディア通信の状態が変化した時に発火するイベント
        virtual void OnConnectionStateChanged(const ConnectionState state) {}
    };
    /// @cond INTERNAL_SECTION
    class InternalListener {
    public:
        virtual void OnChangePreferredEncoding(std::shared_ptr<Subscription> subscription) = 0;
    };
    class Callback {
    public:
        virtual const std::optional<nlohmann::json> GetStatsReport(
            std::shared_ptr<Subscription> subscription) = 0;
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
    virtual std::shared_ptr<interface::Publication> Publication() const = 0;
    /// @brief このSubscriptionをSubscribeしているMemberを取得します。
    virtual std::shared_ptr<interface::Member> Subscriber() const = 0;
    /// @brief State(公開状態がEnableかDisabelかCancelか)を取得します。
    virtual SubscriptionState State() = 0;
    /// @brief Publisherが持つStreamを取得します。
    /// @details
    /// `LocalPerson.subscribe`の返り値でSubscriptionを入手した場合、入手時点で値がsetされています。
    /// その他、イベントの発火によってSubscriptionを取得した場合、まだ値がsetされていない可能性があります。
    virtual std::shared_ptr<RemoteStream> Stream() = 0;
    /// @brief このSubscriptionの優先エンコーディングIDを取得します。
    virtual std::optional<std::string> PreferredEncodingId() const = 0;
    /// @brief 受信するエンコード設定を切り替えます。
    virtual bool ChangePreferredEncoding(const std::string& id) = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief Subscribeを中止します。
    [[deprecated]] virtual bool Cancel() const = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief 統計情報を取得します。
    [[deprecated]] virtual std::optional<model::WebRTCStats> GetStats() = 0;
    /// @cond INTERNAL_SECTION
    virtual void AddGetStatsCallback(Callback* callback) = 0;
    virtual void RemoveGetStatsCallback()                = 0;

    virtual void SetStream(std::shared_ptr<RemoteStream> stream) = 0;
    virtual void SetPreferredEncodingId(const std::string& id)   = 0;

    virtual void OnCanceled() = 0;
    /// @endcond
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_SUBSCRIPTION_HPP_ */
