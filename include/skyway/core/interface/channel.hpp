//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_CHANNEL_HPP_
#define SKYWAY_CORE_INTERFACE_CHANNEL_HPP_

#include "skyway/core/interface/local_person.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/model/domain.hpp"
#include "skyway/rtc_api/channel_state.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"

namespace skyway {
namespace core {
namespace interface {

enum class ChannelState { kOpened, kClosed };

class Channel : public std::enable_shared_from_this<Channel> {
public:
    class EventListener {
    public:
        virtual void OnClosed() {}

        virtual void OnMetadataUpdated(const std::string& metadata) {}

        virtual void OnMemberListChanged() {}

        virtual void OnMemberJoined(std::shared_ptr<interface::Member> member) {}

        virtual void OnMemberLeft(std::shared_ptr<interface::Member> member) {}

        virtual void OnMemberMetadataUpdated(std::shared_ptr<interface::Member> member,
                                             const std::string& metadata) {}

        virtual void OnPublicationMetadataUpdated(
            std::shared_ptr<interface::Publication> publication, const std::string& metadata) {}

        virtual void OnPublicationListChanged() {}

        virtual void OnStreamPublished(std::shared_ptr<interface::Publication> publication) {}

        virtual void OnStreamUnpublished(std::shared_ptr<interface::Publication> publication) {}

        virtual void OnPublicationEnabled(std::shared_ptr<interface::Publication> publication) {}

        virtual void OnPublicationDisabled(std::shared_ptr<interface::Publication> publication) {}

        virtual void OnSubscriptionListChanged() {}

        virtual void OnPublicationSubscribed(
            std::shared_ptr<interface::Subscription> subscription) {}

        virtual void OnPublicationUnsubscribed(
            std::shared_ptr<interface::Subscription> subscription) {}
    };

    virtual ~Channel() = default;

    virtual void AddEventListener(EventListener* listener) = 0;

    virtual void RemoveEventListener(EventListener* listener) = 0;

    virtual std::string Id() const = 0;

    virtual std::optional<std::string> Name() const = 0;

    virtual std::optional<std::string> Metadata() const = 0;

    virtual std::shared_ptr<interface::LocalPerson> LocalPerson() = 0;

    virtual std::vector<std::shared_ptr<interface::RemoteMember>> Bots(bool active_only = true) = 0;

    virtual std::vector<std::shared_ptr<interface::Member>> Members(bool active_only = true) = 0;

    virtual std::vector<std::shared_ptr<interface::Publication>> Publications(
        bool active_only = true) = 0;

    virtual std::vector<std::shared_ptr<interface::Subscription>> Subscriptions(
        bool active_only = true) = 0;

    virtual ChannelState State() const = 0;

    virtual std::shared_ptr<interface::LocalPerson> Join(const model::Member::Init& init) = 0;

    virtual bool Leave(std::shared_ptr<interface::Member> member) = 0;

    virtual bool Close() = 0;

    virtual void Dispose(bool remove_myself_if_needed) = 0;

    virtual bool UpdateMetadata(const std::string& metadata) = 0;

    virtual std::shared_ptr<interface::Member> FindMember(const std::string& member_id,
                                                          bool active_only = true) = 0;

    virtual std::shared_ptr<interface::RemoteMember> FindRemoteMember(const std::string& member_id,
                                                                      bool active_only = true) = 0;

    virtual std::shared_ptr<interface::Publication> FindPublication(
        const std::string& publication_id, bool active_only = true) = 0;

    virtual std::shared_ptr<interface::Subscription> FindSubscription(
        const std::string& subscription_id, bool active_only = true) = 0;

    virtual std::vector<std::shared_ptr<interface::Subscription>> GetSubscriptionsByPublicationId(
        const std::string& publication_id, bool active_only = true) = 0;

    virtual std::vector<std::shared_ptr<interface::Subscription>> GetSubscriptionsBySubscriberId(
        const std::string& subscriber_id, bool active_only = true) = 0;

    virtual std::vector<std::shared_ptr<interface::Publication>> GetPublicationsByPublisherId(
        const std::string& publisher_id, bool active_only = true) = 0;

    virtual std::optional<model::Member> GetMemberDto(const std::string& member_id) const = 0;
    virtual std::optional<model::Publication> GetPublicationDto(
        const std::string& publication_id) const = 0;
    virtual std::optional<model::Subscription> GetSubscriptionDto(
        const std::string& subscription_id) const = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
