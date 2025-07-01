//
//  event_listener_repository.hpp
//  skyway
//
//  Created by sandabu on 2024/04/18.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_RTC_API_INTERFACE_EVENT_LISTENER_REPOSITORY_HPP_
#define SKYWAY_RTC_API_INTERFACE_EVENT_LISTENER_REPOSITORY_HPP_

#include "skyway/rtc_api/interface/api_client.hpp"
#include "skyway/rtc_api/interface/rpc.hpp"

namespace skyway {
namespace rtc_api {
namespace interface {

/// イベントリスナーを管理するリポジトリ
class EventListenerRepository : public Rpc::Listener {
public:
    class Listener {
    public:
        virtual void OnEvent(const nlohmann::json& event) = 0;
        virtual void OnReconnected()                      = 0;
    };
    virtual ~EventListenerRepository() = default;

    virtual void AddListener(const std::string& channel_id, Listener* listener) = 0;
    virtual void RemoveListener(Listener* listener)                             = 0;
    virtual void StartQueuingEvents() = 0;
    virtual void ResolveQueuingEvents() = 0;
};

}  // namespace interface
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_INTERFACE_EVENT_LISTENER_REPOSITORY_HPP_ */
