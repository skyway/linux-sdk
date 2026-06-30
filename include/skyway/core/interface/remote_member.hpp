//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_HPP_
#define SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_HPP_

#include <unordered_map>

#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/stream.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class Channel;

using LocalPersonId  = std::string;
using SubscriptionId = std::string;

class RemoteMember : public Member {
public:
    virtual ~RemoteMember() = default;

    virtual void Dispose(){};

    virtual void OnSubscribedLocalPersonsPublication(
        std::shared_ptr<core::interface::Publication> publication,
        const SubscriptionId& subscription_id){};

    virtual void OnUnsubscribedLocalPersonsPublication(
        std::shared_ptr<core::interface::Publication> publication){};

    virtual void OnLocalPersonSubscribed(std::shared_ptr<interface::Subscription> subscription){};

    virtual void OnLocalPersonUnsubscribed(std::shared_ptr<interface::Subscription> subscription){};

    virtual void OnPublicationSubscribed(std::shared_ptr<interface::Subscription> subscription) {}

    virtual void OnPublicationUnsubscribed(std::shared_ptr<interface::Subscription> subscription) {}

protected:
    RemoteMember(std::shared_ptr<interface::Channel> channel, const model::Member& dto);
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
