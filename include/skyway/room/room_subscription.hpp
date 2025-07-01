//
//  room_subscription.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/08.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
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
    RoomSubscription(std::shared_ptr<core::interface::Subscription> core,
                     interface::RoomDomainFactory* factory);
    ~RoomSubscription();
    std::string Id() override;
    model::ContentType ContentType() override;
    std::shared_ptr<interface::RoomPublication> Publication() override;
    std::shared_ptr<interface::RoomMember> Subscriber() override;
    core::interface::SubscriptionState State() override;
    std::shared_ptr<core::interface::RemoteStream> Stream() override;
    std::optional<std::string> PreferredEncodingId() override;

    void AddEventListener(interface::RoomSubscription::EventListener* listener) override;
    void RemoveEventListener(interface::RoomSubscription::EventListener* listener) override;
    bool ChangePreferredEncoding(const std::string& id) override;
    bool Cancel() override;
    std::optional<model::WebRTCStats> GetStats() override;

private:
    // core::interface::Subscription::EventListener
    void OnCanceled() override;
    //    void OnEnabled() override;
    //    void OnDisabled() override;
    void OnConnectionStateChanged(const core::ConnectionState state) override;

    std::shared_ptr<core::interface::Subscription> core_;
    interface::RoomDomainFactory* factory_;
    std::mutex listener_mtx_;
    interface::RoomSubscription::EventListener* listener_;
};

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ROOM_SUBSCRIPTION_HPP */
