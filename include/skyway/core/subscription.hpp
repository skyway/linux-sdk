//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_SUBSCRIPTION_HPP_
#define SKYWAY_CORE_SUBSCRIPTION_HPP_

#include <functional>

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {

class Subscription : public interface::Subscription {
public:
    Subscription(std::shared_ptr<interface::Channel> channel,
                 const model::Subscription& initial_dto,
                 model::ContentType content_type);

    void AddEventListener(interface::Subscription::EventListener* listener) override;
    void RemoveEventListener(interface::Subscription::EventListener* listener) override;

    void AddInternalListener(interface::Subscription::InternalListener* listener) override;
    void RemoveInternalListener(interface::Subscription::InternalListener* listener) override;

    std::string Id() const override;
    model::ContentType ContentType() const override;
    std::shared_ptr<interface::Publication> Publication() const override;
    std::shared_ptr<interface::Member> Subscriber() const override;
    interface::SubscriptionState State() override;

    std::shared_ptr<interface::RemoteStream> Stream() override;
    std::optional<std::string> PreferredEncodingId() const override;

    bool ChangePreferredEncoding(const std::string& id) override;
    std::optional<model::WebRTCStats> GetStats() override;

    void AddGetStatsCallback(std::weak_ptr<Callback> callback) override;
    void RemoveGetStatsCallback() override;

    void SetStream(std::shared_ptr<interface::RemoteStream> stream) override;
    void SetPreferredEncodingId(const std::string& id) override;

    void OnCanceled() override;
    void OnConnectionStateChanged(const core::ConnectionState new_state) override;

private:
    void DispatchSubscriptionListeners(
        std::function<void(interface::Subscription::EventListener*)> fn);

    std::weak_ptr<interface::Channel> channel_;
    model::Subscription initial_dto_;
    model::ContentType content_type_;
    std::atomic<interface::SubscriptionState> state_;
    std::weak_ptr<interface::Member> subscriber_;
    std::mutex stream_mtx_;
    std::shared_ptr<interface::RemoteStream> stream_;
    std::optional<std::string> preferred_encoding_id_;

    std::mutex listeners_mtx_;
    std::unordered_set<interface::Subscription::EventListener*> listeners_;
    std::mutex internal_listeners_mtx_;
    std::unordered_set<interface::Subscription::InternalListener*> internal_listeners_;
    std::mutex get_stats_callback_mutex_;
    std::weak_ptr<Callback> get_stats_callback_;

public:
    friend class CoreSubscriptionTest;
};

}  // namespace core
}  // namespace skyway

#endif
