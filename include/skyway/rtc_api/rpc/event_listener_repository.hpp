//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_
#define SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_

#include <atomic>
#include <memory>
#include <vector>

#include "skyway/global/worker.hpp"
#include "skyway/rtc_api/interface/api_client.hpp"
#include "skyway/rtc_api/interface/event_listener_repository.hpp"

namespace skyway {
namespace rtc_api {
namespace rpc {

struct Event {
    std::string channel_id;
    nlohmann::json data;
};

struct EventListener {
    std::string channel_id;
    std::weak_ptr<interface::EventListenerRepository::Listener> listener;
    std::unique_ptr<global::interface::Worker> worker = nullptr;
    EventListener(const std::string& channel_id,
                  std::weak_ptr<interface::EventListenerRepository::Listener> listener);
};

class EventListenerRepository : public interface::EventListenerRepository {
public:
    void AddListener(const std::string& channel_id,
                     std::weak_ptr<interface::EventListenerRepository::Listener> listener) override;
    void RemoveListener(const std::string& channel_id) override;
    void StartQueuingEvents() override;
    void ResolveQueuingEvents() override;

    // Impl RpcInterface::Listener
    void OnNotified(const dto::RequestMessage& message) override;
    void OnReconnected() override;

private:
    void Notify(const Event& event);
    void QueueTheEvent(const Event& event);

    std::mutex event_listeners_mtx_;
    std::vector<EventListener> event_listeners_;
    std::atomic<bool> is_queuing_                                           = false;
    std::mutex pending_events_mtx_;
    std::vector<Event> pending_events_ = {};

public:
    friend class EventListenerRepositoryTest;
};

}  // namespace rpc
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_ */
