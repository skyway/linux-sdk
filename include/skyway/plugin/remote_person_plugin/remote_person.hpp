//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_REMOTE_PERSON_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_REMOTE_PERSON_HPP_

#include "skyway/core/ice/ice_manager.hpp"
#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"
#include "skyway/core/interface/stream.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/plugin/remote_person_plugin/connection/p2p_connection.hpp"

namespace skyway {
namespace plugin {
namespace remote_person {

using SubscriptionId        = std::string;

/// @brief RemotePersonの機能を持つメンバー
/// @details 他のSDKで生成されたRemoteMemberで、WebRTCコネクションにてStreamの受け渡しを行います。
class RemotePerson : public core::interface::RemoteMember {
public:
    class EventListener : public core::interface::Member::EventListener {
    public:
        virtual void OnPublicationSubscribed(std::shared_ptr<core::interface::Subscription> subscription) {}
        virtual void OnPublicationUnsubscribed(std::shared_ptr<core::interface::Subscription> subscription) {}
    };
    RemotePerson(
        std::shared_ptr<core::interface::Channel> channel,
        const model::Member& dto,
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory);
    ~RemotePerson();
    /// @brief Subscribeをさせます。
    ///
    /// @details 得られるSubscriptionにはStreamは含まれません。
    ///
    /// また、このSDKで生成したLocalPersonをChannel::Findなどを利用してRemotePersonとして振る舞わせた場合はSubscribeは失敗し、その挙動は未定義です。
    ///
    /// 単純にLocalPerson.Subscribeを利用してください。
    ///
    /// @param publication_id SubscribeするPublicationのID
    std::shared_ptr<core::interface::Subscription> Subscribe(const std::string& publication_id);

    /// @brief Subscribeを中止させます。
    ///
    /// @details
    /// このSDKで生成したLocalPersonをChannel::Findなどを利用してRemotePersonとして振る舞わせた場合はSubscribeは失敗し、その挙動は未定義です。
    /// @param subscription_id 中止対象のSubscriptionID
    bool Unsubscribe(const std::string& subscription_id);

    /// @cond INTERNAL_SECTION
    /// @brief このRemotePersonがLocalPersonのPublicationをSubscribeしたときのイベント
    ///
    /// @details
    /// 実装はRemotePersonではなく、LocalPersonの振る舞いを記述することに気をつけてください。
    ///
    /// LocalPersonがDataPlaneにおいて、Senderとしての接続を開始します。
    /// @param publication LocalPersonのPublication
    /// @param subscription_id SubscriptionのID
    void OnSubscribedLocalPersonsPublication(std::shared_ptr<core::interface::Publication> publication,
                                             const SubscriptionId& subscription_id) override;

    /// @brief このRemotePersonがLocalPersonのPublicationをUnsubscribeしたときのイベント
    ///
    /// @details
    /// 実装はRemotePersonではなく、LocalPersonの振る舞いを記述することに気をつけてください。
    ///
    /// LocalPersonがDataPlaneにおいて、Senderとしての接続を終了します。
    /// @param publication LocalPersonのPublication
    void OnUnsubscribedLocalPersonsPublication(std::shared_ptr<core::interface::Publication> publication) override;

    /// @brief LocalPersonがこのRemotePersonのPublicationをSubscribeした時のイベント
    ///
    /// @details
    /// 実装はRemotePersonではなく、LocalPersonの振る舞いを記述することに気をつけてください。
    ///
    /// LocalPersonがDataPlaneにおいて、Receiverとしての接続を開始します。
    /// @param subscription LocalPersonのSubscription
    void OnLocalPersonSubscribed(std::shared_ptr<core::interface::Subscription> subscription) override;

    /// @brief LocalPersonがこのRemotePersonのPublicationをUnsubscribeした時のイベント
    ///
    /// @details
    /// 実装はRemotePersonではなく、LocalPersonの振る舞いを記述することに気をつけてください。
    ///
    /// LocalPersonがDataPlaneにおいて、Receiverとしての接続を終了します。
    /// @param subscription LocalPersonのSubscription
    void OnLocalPersonUnsubscribed(std::shared_ptr<core::interface::Subscription> subscription) override;
    
    void OnPublicationSubscribed(std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnPublicationUnsubscribed(std::shared_ptr<core::interface::Subscription> subscription) override;

    // core::interface::Member
    void OnLeft() override;

    void Dispose() override;
    /// @endcond

private:
    connection::P2PConnection* GetOrCreateConnection();
    connection::P2PConnection* CreateConnection();
    bool IsLocalPersonSubscribing();
    bool IsSubscribingLocalPersonsPublication();
    bool ShouldClose();
    void CloseConnection();

    std::mutex connection_mtx_;
    std::unique_ptr<connection::P2PConnection> connection_;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
    std::unique_ptr<core::interface::IceManager> ice_manager_;
};

}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_REMOTE_PERSON_HPP_ */
