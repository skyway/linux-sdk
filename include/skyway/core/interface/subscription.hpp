//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_SUBSCRIPTION_HPP_
#define SKYWAY_CORE_INTERFACE_SUBSCRIPTION_HPP_

#include "skyway/core/connection_state.hpp"
#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/remote_stream.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class Publication;

enum class SubscriptionState { kEnabled, kDisabled, kCanceled };

class Subscription : public std::enable_shared_from_this<Subscription>,
                     public ConnectionStateChangeNotifiable {
public:
    class EventListener {
    public:
        virtual void OnConnectionStateChanged(const ConnectionState state) {}

        virtual void OnStreamAttached(std::shared_ptr<RemoteStream> stream) {}
    };

    class InternalListener {
    public:
        virtual void OnChangePreferredEncoding(std::shared_ptr<Subscription> subscription) = 0;
    };
    class Callback {
    public:
        virtual const std::optional<nlohmann::json> GetStatsReport(
            std::shared_ptr<Subscription> subscription) = 0;
    };

    virtual ~Subscription() = default;

    virtual void AddEventListener(EventListener* listener) = 0;

    virtual void RemoveEventListener(EventListener* listener) = 0;

    virtual void AddInternalListener(InternalListener* listener)    = 0;
    virtual void RemoveInternalListener(InternalListener* listener) = 0;

    virtual std::string Id() const = 0;

    virtual model::ContentType ContentType() const = 0;

    virtual std::shared_ptr<interface::Publication> Publication() const = 0;

    virtual std::shared_ptr<interface::Member> Subscriber() const = 0;

    virtual SubscriptionState State() = 0;

    virtual std::shared_ptr<RemoteStream> Stream() = 0;

    virtual std::optional<std::string> PreferredEncodingId() const = 0;

    virtual bool ChangePreferredEncoding(const std::string& id) = 0;

    [[deprecated]] virtual std::optional<model::WebRTCStats> GetStats() = 0;

    virtual void AddGetStatsCallback(std::weak_ptr<Callback> callback) = 0;
    virtual void RemoveGetStatsCallback()                              = 0;

    virtual void SetStream(std::shared_ptr<RemoteStream> stream) = 0;
    virtual void SetPreferredEncodingId(const std::string& id)   = 0;

    virtual void OnCanceled() = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
