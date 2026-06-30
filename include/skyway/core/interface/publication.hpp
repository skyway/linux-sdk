//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_PUBLICATION_HPP_
#define SKYWAY_CORE_INTERFACE_PUBLICATION_HPP_

#include "skyway/core/connection_state.hpp"
#include "skyway/core/interface/local_media_stream.hpp"
#include "skyway/core/interface/local_stream.hpp"
#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/subscription.hpp"

namespace skyway {
namespace core {
namespace interface {

using LocalStream = interface::LocalStream;

enum class PublicationState { kEnabled, kDisabled, kCanceled };

class Publication : public std::enable_shared_from_this<Publication>,
                    public ConnectionStateChangeNotifiable {
public:
    class EventListener {
    public:
        virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription) {}

        virtual void OnUnsubscribed(std::shared_ptr<interface::Subscription> subscription) {}

        virtual void OnSubscriptionListChanged() {}

        virtual void OnMetadataUpdated(const std::string& metadata) {}

        virtual void OnEnabled() {}

        virtual void OnDisabled() {}

        virtual void OnStateChanged() {}

        virtual void OnConnectionStateChanged(const core::ConnectionState new_state) {}
    };

    class InternalListener {
    public:
        virtual void OnEncodingsUpdated(std::shared_ptr<interface::Publication> publication,
                                        std::vector<model::Encoding> encodings) {}
        virtual void OnStreamReplaced(std::shared_ptr<interface::Publication> publication,
                                      std::shared_ptr<LocalMediaStream> stream) {}
        virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription) {}
    };
    class Callback {
    public:
        virtual const std::optional<nlohmann::json> GetStatsReport(
            std::shared_ptr<interface::Publication> publication) = 0;
    };

    virtual ~Publication() = default;

    virtual void AddEventListener(EventListener* listener) = 0;

    virtual void RemoveEventListener(EventListener* listener) = 0;

    virtual void AddInternalListener(InternalListener* listener)    = 0;
    virtual void RemoveInternalListener(InternalListener* listener) = 0;

    virtual std::string Id() const = 0;

    virtual std::shared_ptr<interface::Member> Publisher() const = 0;

    virtual std::vector<std::shared_ptr<interface::Subscription>> Subscriptions() const = 0;
    virtual model::PublicationType Type() const                                         = 0;

    virtual model::ContentType ContentType() const = 0;

    virtual std::optional<std::string> Metadata() const = 0;

    virtual std::shared_ptr<interface::Publication> Origin() const = 0;

    virtual std::vector<model::Codec> CodecCapabilities() const = 0;

    virtual std::vector<model::Encoding> Encodings() const = 0;

    virtual PublicationState State() = 0;

    virtual std::shared_ptr<LocalStream> Stream() const = 0;

    virtual bool UpdateMetadata(const std::string& metadata) = 0;

    virtual bool UpdateEncodings(std::vector<model::Encoding> encodings) = 0;

    virtual bool ReplaceStream(std::shared_ptr<LocalStream> stream) = 0;

    virtual bool Enable() = 0;

    virtual bool Disable() const = 0;

    [[deprecated]] virtual std::optional<model::WebRTCStats> GetStats(
        const std::string& selector) = 0;

    virtual void AddGetStatsCallback(const std::string& remote_member_id,
                                     std::weak_ptr<Callback> callback)       = 0;
    virtual void RemoveGetStatsCallback(const std::string& remote_member_id) = 0;

    virtual void SetCodecCapabilities(std::vector<model::Codec> codec_capabilities) = 0;
    virtual void SetEncodings(std::vector<model::Encoding> encodings)               = 0;
    virtual void SetStream(std::shared_ptr<LocalStream> stream)                     = 0;
    virtual bool IsEnabling()                                                       = 0;
    virtual void Dispose()                                                          = 0;

    virtual void OnUnpublished()                                                       = 0;
    virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription)   = 0;
    virtual void OnUnsubscribed(std::shared_ptr<interface::Subscription> subscription) = 0;
    virtual void OnMetadataUpdated(const std::string& metadata)                        = 0;
    virtual void OnEnabled()                                                           = 0;
    virtual void OnDisabled()                                                          = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
