//
//  remote_person.hpp
//  skyway
//
//  Created by sandabu on 2021/12/21.
//  Copyright © 2021 NTT Communications. All rights reserved.
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

using RemoteMemberInterface = core::interface::RemoteMember;
using PublicationInterface  = core::interface::Publication;
using SubscriptionInterface = core::interface::Subscription;
using MemberInterface       = core::interface::Member;
using SubscriptionId        = std::string;

/// @brief RemotePersonの機能を持つメンバー
/// @details 他のSDKで生成されたRemoteMemberで、WebRTCコネクションにてStreamの受け渡しを行います。
class RemotePerson : public RemoteMemberInterface,
                     public core::interface::Channel::InternalEventListener {
public:
    class EventListener : public MemberInterface::EventListener {
    public:
        virtual void OnPublicationSubscribed(SubscriptionInterface* subscription) {}
        virtual void OnPublicationUnsubscribed(SubscriptionInterface* subscription) {}
    };
    RemotePerson(
        core::interface::Channel* channel,
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
    SubscriptionInterface* Subscribe(const std::string& publication_id);

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
    void OnSubscribedLocalPersonsPublication(PublicationInterface* publication,
                                             const SubscriptionId& subscription_id) override;

    /// @brief このRemotePersonがLocalPersonのPublicationをUnsubscribeしたときのイベント
    ///
    /// @details
    /// 実装はRemotePersonではなく、LocalPersonの振る舞いを記述することに気をつけてください。
    ///
    /// LocalPersonがDataPlaneにおいて、Senderとしての接続を終了します。
    /// @param publication LocalPersonのPublication
    void OnUnsubscribedLocalPersonsPublication(PublicationInterface* publication) override;

    /// @brief LocalPersonがこのRemotePersonのPublicationをSubscribeした時のイベント
    ///
    /// @details
    /// 実装はRemotePersonではなく、LocalPersonの振る舞いを記述することに気をつけてください。
    ///
    /// LocalPersonがDataPlaneにおいて、Receiverとしての接続を開始します。
    /// @param subscription LocalPersonのSubscription
    void OnLocalPersonSubscribed(SubscriptionInterface* subscription) override;

    /// @brief LocalPersonがこのRemotePersonのPublicationをUnsubscribeした時のイベント
    ///
    /// @details
    /// 実装はRemotePersonではなく、LocalPersonの振る舞いを記述することに気をつけてください。
    ///
    /// LocalPersonがDataPlaneにおいて、Receiverとしての接続を終了します。
    /// @param subscription LocalPersonのSubscription
    void OnLocalPersonUnsubscribed(SubscriptionInterface* subscription) override;

    // core::interface::Member
    void OnLeft() override;

    // core::interface::Channel::InternalEventListener
    void OnPublicationSubscribed(SubscriptionInterface* subscription) override;
    void OnPublicationUnsubscribed(SubscriptionInterface* subscription) override;

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
    std::unique_ptr<global::interface::Worker> worker_ = std::make_unique<global::Worker>();
};

}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_REMOTE_PERSON_HPP_ */
