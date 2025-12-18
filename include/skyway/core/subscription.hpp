//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_SUBSCRIPTION_HPP_
#define SKYWAY_CORE_SUBSCRIPTION_HPP_

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {

/// @brief Subscriptionの実装クラス
class Subscription : public interface::Subscription {
public:
    /// @cond INTERNAL_SECTION
    Subscription(std::shared_ptr<interface::Channel> channel, const model::Subscription& initial_dto, model::ContentType content_type);
    /// @endcond

    void AddEventListener(interface::Subscription::EventListener* listener) override;
    void RemoveEventListener(interface::Subscription::EventListener* listener) override;
    /// @cond INTERNAL_SECTION
    void AddInternalListener(interface::Subscription::InternalListener* listener) override;
    void RemoveInternalListener(interface::Subscription::InternalListener* listener) override;
    /// @endcond

    std::string Id() const override;
    model::ContentType ContentType() const override;
    std::shared_ptr<interface::Publication> Publication() const override;
    std::shared_ptr<interface::Member> Subscriber() const override;
    interface::SubscriptionState State() override;

    std::shared_ptr<interface::RemoteStream> Stream() override;
    std::optional<std::string> PreferredEncodingId() const override;

    bool ChangePreferredEncoding(const std::string& id) override;
    bool Cancel() const override;
    std::optional<model::WebRTCStats> GetStats() override;
    /// @cond INTERNAL_SECTION
    void AddGetStatsCallback(Callback* callback) override;
    void RemoveGetStatsCallback() override;

    void SetStream(std::shared_ptr<interface::RemoteStream> stream) override;
    void SetPreferredEncodingId(const std::string& id) override;

    void OnCanceled() override;
    void OnConnectionStateChanged(const core::ConnectionState new_state) override;
    /// @endcond
private:
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
    Callback* get_stats_callback_;

public:
    /// @cond INTERNAL_SECTION
    friend class CoreSubscriptionTest;
    /// @endcond
};

}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_SUBSCRIPTION_HPP_ */
