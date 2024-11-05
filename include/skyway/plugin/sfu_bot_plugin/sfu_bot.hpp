//
//  sfu_bot.hpp
//  skyway
//
//  Created by salmon on 2022/1/25.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_BOT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_BOT_HPP_

#include <unordered_map>

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/ice_manager.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"
#include "skyway/core/interface/stream.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_connection.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_connection_factory.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport_repository.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

/// @brief SfuBotの機能を持つメンバー
class SfuBot : public core::interface::RemoteMember,
               public core::interface::Channel::InternalEventListener {
public:
    // TODO: Impl EventListener
    SfuBot(core::interface::Channel* channel,
           const model::Member& dto,
           interface::SfuApiClient* client,
           rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
           interface::TransportRepository* transport_repo,
           std::unique_ptr<interface::SfuConnectionFactory> connection_factory,
           std::unique_ptr<core::interface::IceManager> ice_manager);
    SfuBot(core::interface::Channel* channel,
           const model::Member& dto,
           interface::SfuApiClient* client,
           rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
           interface::TransportRepository* transport_repo);
    ~SfuBot();
    /// @brief Forwarding一覧
    std::vector<Forwarding*> Forwardings();
    /// @brief PublicationをForwardingします。
    Forwarding* StartForwarding(core::interface::Publication* publication,
                                const ForwardingConfigure configure);
    /// @brief Forwarding停止します。
    bool StopForwarding(Forwarding* forwarding);

    /// @cond INTERNAL_SECTION
    // Impl core::interface::RemoteMember
    void Dispose() override;
    void OnUnsubscribedLocalPersonsPublication(PublicationInterface* publication) override;
    void OnLocalPersonSubscribed(core::interface::Subscription* subscription) override;
    void OnLocalPersonUnsubscribed(core::interface::Subscription* subscription) override;

    // Impl core::interface::Member
    void OnLeft() override;

    // Impl core::interface::Channel::InternalEventListener
    void OnPublicationSubscribed(core::interface::Subscription* subscription) override;
    /// @endcond

private:
    bool StopForwarding(Forwarding* forwarding, bool with_api_request);
    interface::SfuConnection* CreateConnection();
    interface::SfuConnection* GetOrCreateConnection();
    bool ConfirmSubscription(Forwarding* forwarding, core::interface::Subscription* subscription);

    interface::SfuApiClient* client_;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
    interface::TransportRepository* transport_repo_;
    std::unique_ptr<interface::SfuConnectionFactory> connection_factory_;
    std::unique_ptr<interface::SfuConnection> connection_;
    std::unique_ptr<core::interface::IceManager> ice_manager_;
    std::mutex connection_mtx_;
    std::mutex stop_forwarding_mtx_;
    std::mutex receiving_mtx_;
    using ForwardingId = std::string;
    std::unordered_map<ForwardingId, std::unique_ptr<Forwarding>> forwardings_;
    // Mutex for `forwardings_`
    std::mutex forwardings_mtx_;

public:
    /// @cond INTERNAL_SECTION
    friend class SfuBotTest;
    /// @endcond
};

}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_BOT_HPP_ */
