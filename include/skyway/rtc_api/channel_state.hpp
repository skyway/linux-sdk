//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_CHANNEL_STATE_HPP_
#define SKYWAY_RTC_API_CHANNEL_STATE_HPP_

#include <atomic>
#include <json.hpp>
#include <mutex>
#include <optional>
#include <set>
#include <thread>

#include "skyway/global/interface/worker.hpp"
#include "skyway/model/domain.hpp"
#include "skyway/rtc_api/dto/event.hpp"
#include "skyway/rtc_api/interface/api_client.hpp"
#include "skyway/rtc_api/interface/channel_state.hpp"
#include "skyway/rtc_api/interface/event_listener_repository.hpp"

namespace skyway {
namespace rtc_api {

class ChannelState : public interface::ChannelState,
                     public interface::EventListenerRepository::Listener,
                     public std::enable_shared_from_this<ChannelState> {
public:
    ~ChannelState();
    ChannelState(const model::Channel& channel,
                 std::optional<uint64_t> version,
                 std::weak_ptr<interface::EventListenerRepository> event_listener_repository,
                 interface::ApiClient* api);

    std::string Id() override;
    std::optional<std::string> Name() override;
    std::optional<std::string> Metadata() override;
    std::vector<model::Member> Members() override;
    std::vector<model::Publication> Publications() override;
    std::vector<model::Subscription> Subscriptions() override;
    uint64_t Version() override;
    void RegisterEventListener(std::weak_ptr<EventListener> listener) override;
    void UnregisterEventListener() override;
    void Dispose() override;

    void OnEvent(const nlohmann::json& event) override;
    void OnReconnected() override;

private:
    uint64_t ExpectedNextVersion();
    void QueueEvent(const nlohmann::json& event);
    void ResolveEvents();
    void JoinPacketLossCheckerThread();
    bool ResubscribingChannelEvents();

    void HandleEvent(const nlohmann::json& event, uint64_t version);

    void OnChannelDeleted();
    void OnChannelMetadataUpdated(const dto::ChannelMetadataUpdatedEventData& data);
    void OnMemberAdded(const dto::MemberAddedEventData& data);
    void OnMemberRemoved(const dto::MemberRemovedEventData& data);
    void OnMemberMetadataUpdated(const dto::MemberMetadataUpdatedEventData& data);
    void OnStreamPublished(const dto::StreamPublishedEventData& data);
    void OnStreamUnpublished(const dto::StreamUnpublishedEventData& data);
    void OnPublicationEnabled(const dto::PublicationEnabledEventData& data);
    void OnPublicationDisabled(const dto::PublicationDisabledEventData& data);
    void OnPublicationMetadataUpdated(const dto::PublicationMetadataUpdatedEventData& data);
    void OnPublicationSubscribed(const dto::StreamSubscribedEventData& data);
    void OnPublicationUnsubscribed(const dto::StreamUnsubscribedEventData& data);

    model::Channel channel_;
    std::mutex channel_mtx_;
    std::mutex event_mtx_;
    std::weak_ptr<EventListener> listener_;
    std::mutex listener_mtx_;

    std::string channel_id_;
    std::optional<uint64_t> observed_version_;
    std::mutex version_mtx_;
    std::weak_ptr<interface::EventListenerRepository> event_listener_repository_;
    interface::ApiClient* api_;
    std::set<nlohmann::json> queued_events_;
    std::mutex queued_events_mtx_;
    std::unique_ptr<std::thread> packet_loss_checker_thread_;
    std::atomic<bool> packet_loss_checker_canceled_ = false;
    std::atomic<bool> is_disposed_                  = false;
    std::unique_ptr<global::interface::Worker> worker_;

public:
    friend class RtcApiChannelStateTest;
};

}  // namespace rtc_api
}  // namespace skyway

#endif
