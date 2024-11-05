//
//  room_subscription.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/08.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_ROOM_ROOM_SUBSCRIPTION_HPP
#define SKYWAY_ROOM_ROOM_SUBSCRIPTION_HPP

#include <skyway/core/interface/subscription.hpp>

#include "skyway/room/interface/room_domain_factory.hpp"
#include "skyway/room/interface/room_subscription.hpp"

namespace skyway {
namespace room {

/// @brief RoomSubscriptionの操作を行うクラス
class RoomSubscription : public interface::RoomSubscription,
                         public core::interface::Subscription::EventListener {
public:
    RoomSubscription(core::interface::Subscription* core, interface::RoomDomainFactory* factory);
    ~RoomSubscription();
    std::string Id() override;
    model::ContentType ContentType() override;
    std::unique_ptr<interface::RoomPublication> Publication() override;
    std::unique_ptr<interface::RoomMember> Subscriber() override;
    core::interface::SubscriptionState State() override;
    std::shared_ptr<core::interface::RemoteStream> Stream() override;
    boost::optional<std::string> PreferredEncodingId() override;

    void AddEventListener(interface::RoomSubscription::EventListener* listener) override;
    void RemoveEventListener(interface::RoomSubscription::EventListener* listener) override;
    void ChangePreferredEncoding(const std::string& id) override;
    bool Cancel() override;
    boost::optional<model::WebRTCStats> GetStats() override;

private:
    // core::interface::Subscription::EventListener
    void OnCanceled() override;
    //    void OnEnabled() override;
    //    void OnDisabled() override;
    void OnConnectionStateChanged(const core::ConnectionState state) override;

    core::interface::Subscription* core_;
    interface::RoomDomainFactory* factory_;
    std::mutex listener_mtx_;
    interface::RoomSubscription::EventListener* listener_;
};

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ROOM_SUBSCRIPTION_HPP */
