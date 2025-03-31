//
//  channel_state.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/04/17.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_INTERFACE_CHANNEL_STATE_HPP_
#define SKYWAY_RTC_API_INTERFACE_CHANNEL_STATE_HPP_

namespace skyway {
namespace rtc_api {
namespace interface {

class ChannelState {
public:
    class EventListener {
    public:
        virtual void OnChannelDeleted(const std::string& channel_id) {}
        virtual void OnChannelMetadataUpdated(model::Channel* channel) {}
        virtual void OnMemberAdded(const model::Member& member) {}
        virtual void OnMemberRemoved(const std::string& member_id) {}
        virtual void OnMemberMetadataUpdated(const model::Member& member) {}
        virtual void OnStreamPublished(const model::Publication& publication) {}
        virtual void OnStreamUnpublished(const std::string& publication_id) {}
        virtual void OnPublicationEnabled(const model::Publication& publication) {}
        virtual void OnPublicationDisabled(const model::Publication& publication) {}
        virtual void OnPublicationMetadataUpdated(const model::Publication& publication) {}
        virtual void OnPublicationSubscribed(const model::Subscription& subscription) {}
        virtual void OnPublicationUnsubscribed(const std::string& subscription_id) {}
    };
    virtual ~ChannelState() = default;

    virtual std::string Id()                                 = 0;
    virtual std::optional<std::string> Name()                = 0;
    virtual std::optional<std::string> Metadata()            = 0;
    virtual std::vector<model::Member> Members()             = 0;
    virtual std::vector<model::Publication> Publications()   = 0;
    virtual std::vector<model::Subscription> Subscriptions() = 0;
    virtual uint64_t Version()                               = 0;

    /// @brief イベントリスナを登録します。
    /// @details 登録できるリスナは1つであることに注意してください。
    /// @param listener イベントリスナ
    virtual void RegisterEventListener(EventListener* listener) = 0;
    virtual void UnregisterEventListener()                      = 0;

    virtual void Dispose() = 0;
};

}  // namespace interface
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_INTERFACE_CHANNEL_STATE_HPP_ */
