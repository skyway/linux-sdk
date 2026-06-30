//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_LOCAL_PERSON_HPP_
#define SKYWAY_CORE_INTERFACE_LOCAL_PERSON_HPP_

#include "skyway/core/interface/chunk_messenger.hpp"
#include "skyway/core/interface/local_stream.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"

namespace skyway {
namespace core {
namespace interface {

class LocalPerson : public Member {
public:
    class EventListener : public Member::EventListener {
    public:
        virtual void OnStreamPublished(std::shared_ptr<interface::Publication> publication) {}

        virtual void OnStreamUnpublished(std::shared_ptr<interface::Publication> publication) {}

        virtual void OnPublicationSubscribed(
            std::shared_ptr<interface::Subscription> subscription) {}

        virtual void OnPublicationUnsubscribed(
            std::shared_ptr<interface::Subscription> subscription) {}
    };

    struct PublicationOptions {
        std::optional<std::string> metadata;

        std::vector<model::Codec> codec_capabilities;

        std::vector<model::Encoding> encodings;

        bool is_enabled;
        model::PublicationType type;

        PublicationOptions(bool is_enabled             = true,
                           model::PublicationType type = model::PublicationType::kP2P)
            : is_enabled(is_enabled), type(type) {}
    };

    struct SubscriptionOptions {
        bool is_enabled;

        std::optional<std::string> preferred_encoding_id;
        SubscriptionOptions(bool is_enabled = true) : is_enabled(is_enabled) {}
    };
    virtual ~LocalPerson() = default;

    virtual ChunkMessenger* Messenger() const = 0;

    virtual std::shared_ptr<interface::Publication> Publish(std::shared_ptr<LocalStream> stream,
                                                            PublicationOptions options) = 0;

    virtual std::shared_ptr<interface::Subscription> Subscribe(
        const std::string& publication_id, const SubscriptionOptions& options) = 0;

    virtual bool Unpublish(const std::string& publication_id) const = 0;

    virtual bool Unsubscribe(const std::string& subscription_id) const = 0;

    virtual void OnPublished(std::shared_ptr<interface::Publication> publication)   = 0;
    virtual void OnUnpublished(std::shared_ptr<interface::Publication> publication) = 0;
    virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription,
                              std::shared_ptr<interface::RemoteMember> publisher)   = 0;
    virtual void OnUnsubscribed(std::shared_ptr<interface::Subscription> subscription,
                                std::shared_ptr<interface::RemoteMember> publisher) = 0;

    virtual void OnPublicationSubscribedByRemoteMember(
        std::shared_ptr<interface::Subscription> subscription,
        std::shared_ptr<interface::RemoteMember> subscriber) = 0;
    virtual void OnPublicationUnsubscribedByRemoteMember(
        std::shared_ptr<interface::Subscription> subscription,
        std::shared_ptr<interface::RemoteMember> subscriber) = 0;

    virtual void Dispose() = 0;

protected:
    LocalPerson(std::shared_ptr<interface::Channel> channel, const model::Member& dto);
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
