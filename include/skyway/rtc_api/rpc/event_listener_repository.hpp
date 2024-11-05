//
//  event_listener_repository.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2024/04/18.
//  Copyright © 2024 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_
#define SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_

#include <unordered_set>
#include <atomic>

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
    interface::EventListenerRepository::Listener* listener;
    std::unique_ptr<global::interface::Worker> worker = nullptr;
    EventListener(const std::string& channel_id, interface::EventListenerRepository::Listener* listener);
    bool operator==(const EventListener& rhs) const;
    struct Hash {
        std::size_t operator()(const EventListener& event_listener) const;
    };
};

class EventListenerRepository : public interface::EventListenerRepository {
public:
    void AddListener(const std::string& channel_id,
                     interface::EventListenerRepository::Listener* listener) override;
    void RemoveListener(interface::EventListenerRepository::Listener* listener) override;
    void StartQueuingEvents() override;
    void ResolveQueuingEvents() override;

    // Impl RpcInterface::Listener
    void OnNotified(const dto::RequestMessage& message) override;
    void OnReconnected() override;

private:
    void Notify(const Event& event);
    void QueueTheEvent(const Event& event);

    std::mutex event_listeners_mtx_;
    std::unordered_set<EventListener, EventListener::Hash> event_listeners_ = {};
    std::atomic<bool> is_queuing_ = false;
    std::mutex pending_events_mtx_;
    std::vector<Event> pending_events_ = {};

public:
    friend class EventListenerRepositoryTest;
};

}  // namespace rpc
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_RPC_EVENT_LISTENER_REPOSITORY_HPP_ */
