//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_
#define SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "skyway/rtc_api/interface/event_listener_repository.hpp"

namespace skyway {
namespace rtc_api {
namespace rpc {

struct Event {
    std::string channel_id;
    nlohmann::json data;
};

class EventListenerRepository : public interface::EventListenerRepository {
public:
    ~EventListenerRepository();

    void Dispose() override;
    void AddListener(const std::string& channel_id,
                     std::weak_ptr<interface::EventListenerRepository::Listener> listener) override;
    void RemoveListener(
        const std::string& channel_id,
        std::weak_ptr<interface::EventListenerRepository::Listener> listener) override;
    void StartQueuingEvents() override;
    void ResolveQueuingEvents() override;

    void OnNotified(const dto::RequestMessage& message) override;
    void OnReconnected() override;

private:
    void Notify(const Event& event);
    void QueueTheEvent(const Event& event);

    std::atomic<bool> is_disposed_ = false;
    std::mutex listeners_mtx_;
    using ChannelId = std::string;
    std::unordered_map<ChannelId,
                       std::vector<std::weak_ptr<interface::EventListenerRepository::Listener>>>
        listeners_;
    std::atomic<bool> is_queuing_ = false;
    std::mutex pending_events_mtx_;
    std::vector<Event> pending_events_ = {};

public:
    friend class EventListenerRepositoryTest;
};

}  // namespace rpc
}  // namespace rtc_api
}  // namespace skyway

#endif
