//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_MEMBER_HPP_
#define SKYWAY_CORE_INTERFACE_MEMBER_HPP_

#include <atomic>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_set>

#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class Channel;
class Publication;
class Subscription;

enum class MemberState { kJoined, kLeft };

class Member : public std::enable_shared_from_this<Member> {
public:
    class EventListener {
    public:
        virtual void OnLeft() {}

        virtual void OnMetadataUpdated(const std::string& metadata) {}

        virtual void OnPublicationListChanged() {}

        virtual void OnSubscriptionListChanged() {}
    };
    virtual ~Member() = default;

    void AddEventListener(EventListener* listener);

    void RemoveEventListener(EventListener* listener);

    bool UpdateMetadata(const std::string& metadata);

    bool Leave();

    std::string Id() const;

    std::optional<std::string> Name() const;

    std::optional<std::string> Metadata() const;

    model::MemberType Type() const;

    std::string Subtype() const;

    model::Side Side() const;

    MemberState State() const;

    std::vector<std::shared_ptr<interface::Publication>> Publications() const;

    std::vector<std::shared_ptr<interface::Subscription>> Subscriptions() const;

    virtual void OnLeft();
    void OnMetadataUpdated(const std::string& metadata);
    virtual void OnPublicationListChanged();
    virtual void OnSubscriptionListChanged();

protected:
    void DispatchMemberListeners(std::function<void(EventListener*)> fn);
    Member(std::shared_ptr<interface::Channel> channel,
           const model::Member& initial_dto,
           const model::Side& side);

    std::weak_ptr<interface::Channel> channel_;
    model::Member initial_dto_;
    model::Side side_;
    std::atomic<MemberState> state_;
    std::mutex listeners_mtx_;
    std::unordered_set<EventListener*> listeners_;
    std::atomic<bool> metadata_updated_;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
