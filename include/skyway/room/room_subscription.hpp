//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_ROOM_SUBSCRIPTION_HPP
#define SKYWAY_ROOM_ROOM_SUBSCRIPTION_HPP

#include <mutex>

#include <skyway/core/interface/subscription.hpp>

#include "skyway/room/interface/room_domain_factory.hpp"
#include "skyway/room/interface/room_subscription.hpp"

namespace skyway {
namespace room {

/// @brief RoomSubscriptionの操作を行うクラス
class RoomSubscription : public interface::RoomSubscription {
public:
    /// @cond INTERNAL_SECTION
    RoomSubscription(std::shared_ptr<core::interface::Subscription> core,
                     interface::RoomDomainFactory* factory);
    /// @endcond

    ~RoomSubscription();
    std::string Id() override;
    domain::ContentType ContentType() override;
    std::shared_ptr<interface::RoomPublication> Publication() override;
    std::shared_ptr<interface::RoomMember> Subscriber() override;
    SubscriptionState State() override;
    std::shared_ptr<media::stream::interface::remote::RemoteStream> Stream() override;
    std::optional<std::string> PreferredEncodingId() override;

    void AddEventListener(interface::RoomSubscription::EventListener* listener) override;
    void RemoveEventListener(interface::RoomSubscription::EventListener* listener) override;
    bool ChangePreferredEncoding(const std::string& id) override;
    std::optional<WebRTCStats> GetStats() override;

private:
    class CoreEventListenerAdapter : public core::interface::Subscription::EventListener {
    public:
        CoreEventListenerAdapter(RoomSubscription* outer);
        void OnCanceled();
        void OnConnectionStateChanged(const core::ConnectionState state);
        void OnStreamAttached(std::shared_ptr<core::interface::RemoteStream> stream);

    private:
        RoomSubscription* outer_;
    };

    void SetStream();
    void OnCanceled();
    void OnConnectionStateChanged(const core::ConnectionState state);
    void OnStreamAttached(std::shared_ptr<core::interface::RemoteStream> stream);
    SubscriptionState ConvertToPlatformSubscriptionState(core::interface::SubscriptionState state);

    std::mutex stream_mtx_;
    std::shared_ptr<media::stream::interface::remote::RemoteStream> stream_;

    std::shared_ptr<core::interface::Subscription> core_;
    interface::RoomDomainFactory* factory_;
    std::unique_ptr<CoreEventListenerAdapter> core_event_listener_adapter_;
    std::mutex listener_mtx_;
    interface::RoomSubscription::EventListener* listener_;
};

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ROOM_SUBSCRIPTION_HPP */
