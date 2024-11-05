//
//  channel_state.hpp
//  skyway
//
//  Created by sandabu on 2022/01/11.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_CHANNEL_STATE_HPP_
#define SKYWAY_RTC_API_CHANNEL_STATE_HPP_

#include <json.hpp>

#include "skyway/model/domain.hpp"
#include "skyway/rtc_api/dto/event.hpp"
#include "skyway/rtc_api/event_observer.hpp"
#include "skyway/rtc_api/interface/channel_state.hpp"
#include "skyway/rtc_api/rpc/api_client.hpp"

namespace skyway {
namespace rtc_api {

class ChannelState : public interface::ChannelState, public EventObserver::Listener {
public:
    ChannelState(const model::Channel& channel, const std::unique_ptr<EventObserver> observer);

    std::string Id() override;
    boost::optional<std::string> Name() override;
    boost::optional<std::string> Metadata() override;
    std::vector<model::Member> Members() override;
    std::vector<model::Publication> Publications() override;
    std::vector<model::Subscription> Subscriptions() override;
    uint64_t Version() override;
    void RegisterEventListener(EventListener* listener) override;
    void UnregisterEventListener() override;
    void Dispose() override;

private:
    model::Channel channel_;
    std::mutex channel_mtx_;
    std::mutex event_mtx_;
    std::unique_ptr<EventObserver> observer_;
    EventListener* listener_ = nullptr;
    std::mutex listener_mtx_;

    // Events
    void OnEvent(const nlohmann::json& event, uint64_t version) override;

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
    void OnSubscriptionEnabled(const dto::SubscriptionEnabledEventData& data);
    void OnSubscriptionDisabled(const dto::SubscriptionDisabledEventData& data);

public:
    friend class RtcApiChannelStateTest;
};

}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_CHANNEL_STATE_HPP_ */
