//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_BOT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_BOT_HPP_

#include <unordered_map>

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/ice_manager.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_connection.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_connection_factory.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport_repository.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

class SfuBot : public core::interface::RemoteMember {
public:
    SfuBot(std::shared_ptr<core::interface::Channel> channel,
           const model::Member& dto,
           interface::SfuApiClient* client,
           rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
           interface::TransportRepository* transport_repo,
           std::unique_ptr<interface::SfuConnectionFactory> connection_factory,
           std::unique_ptr<core::interface::IceManager> ice_manager);
    SfuBot(std::shared_ptr<core::interface::Channel> channel,
           const model::Member& dto,
           interface::SfuApiClient* client,
           rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
           interface::TransportRepository* transport_repo);
    ~SfuBot();

    std::vector<Forwarding*> Forwardings();

    Forwarding* StartForwarding(std::shared_ptr<core::interface::Publication> publication,
                                const ForwardingConfigure configure);

    bool StopForwarding(Forwarding* forwarding);

    void Dispose() override;
    void OnUnsubscribedLocalPersonsPublication(
        std::shared_ptr<core::interface::Publication> publication) override;
    void OnLocalPersonSubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnLocalPersonUnsubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnPublicationSubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;

    void OnLeft() override;

private:
    bool StopForwarding(Forwarding* forwarding, bool with_api_request);
    std::shared_ptr<interface::SfuConnection> CreateConnection();
    std::shared_ptr<interface::SfuConnection> GetOrCreateConnection();
    bool ConfirmSubscription(Forwarding* forwarding,
                             std::shared_ptr<core::interface::Subscription> subscription);

    interface::SfuApiClient* client_;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
    interface::TransportRepository* transport_repo_;
    std::unique_ptr<interface::SfuConnectionFactory> connection_factory_;
    std::shared_ptr<interface::SfuConnection> connection_;
    std::unique_ptr<core::interface::IceManager> ice_manager_;
    std::mutex connection_mtx_;
    using ForwardingId = std::string;
    std::unordered_map<ForwardingId, std::unique_ptr<Forwarding>> forwardings_;

    std::mutex forwardings_mtx_;
    std::mutex dispose_mtx_;
    std::atomic<bool> is_disposed_ = false;

public:
    friend class SfuBotTest;
};

}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif
