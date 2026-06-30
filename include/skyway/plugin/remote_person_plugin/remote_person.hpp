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

using SubscriptionId = std::string;

class RemotePerson : public core::interface::RemoteMember {
public:
    class EventListener : public core::interface::Member::EventListener {
    public:
        virtual void OnPublicationSubscribed(
            std::shared_ptr<core::interface::Subscription> subscription) {}
        virtual void OnPublicationUnsubscribed(
            std::shared_ptr<core::interface::Subscription> subscription) {}
    };
    RemotePerson(
        std::shared_ptr<core::interface::Channel> channel,
        const model::Member& dto,
        rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory);
    ~RemotePerson();

    std::shared_ptr<core::interface::Subscription> Subscribe(const std::string& publication_id);

    bool Unsubscribe(const std::string& subscription_id);

    void OnSubscribedLocalPersonsPublication(
        std::shared_ptr<core::interface::Publication> publication,
        const SubscriptionId& subscription_id) override;

    void OnUnsubscribedLocalPersonsPublication(
        std::shared_ptr<core::interface::Publication> publication) override;

    void OnLocalPersonSubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;

    void OnLocalPersonUnsubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;

    void OnPublicationSubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnPublicationUnsubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;

    void OnLeft() override;

    void Dispose() override;

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

#endif
