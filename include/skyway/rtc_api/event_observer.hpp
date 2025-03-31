//
//  event_observer.hpp
//  skyway
//
//  Created by sandabu on 2022/01/17.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_EVENT_OBSERVER_HPP_
#define SKYWAY_RTC_API_EVENT_OBSERVER_HPP_

#include <json.hpp>
#include <mutex>
#include <set>
#include <thread>

#include "skyway/rtc_api/interface/api_client.hpp"
#include "skyway/rtc_api/interface/event_listener_repository.hpp"

namespace skyway {
namespace rtc_api {

class EventObserver : public interface::EventListenerRepository::Listener {
public:
    class Listener {
    public:
        virtual void OnEvent(const nlohmann::json& event, uint64_t version) = 0;
    };

    /// コンストラクタ
    /// - Parameters:
    ///   - version: 初期バージョン
    ///   ChannelCreatedイベントが0なので、新しくChannelを作った場合はstd::nulloptを入力してください
    ///   - channel_id: チャンネルID
    ///   - event_listener_repository: イベントリスナーリポジトリ
    ///   - api: RAPIクライアント
    EventObserver(const std::optional<uint64_t> version,
                  const std::string& channel_id,
                  interface::EventListenerRepository* event_listener_repository,
                  interface::ApiClient* api);
    ~EventObserver();

    void RegisterEventListener(Listener* listener);
    void Dispose();

    // interface::EventListenerRepository::Listener
    void OnEvent(const nlohmann::json& event) override;
    void OnReconnected() override;

private:
    uint64_t ExpectedNextVersion();

    void QueueEvent(const nlohmann::json& event);
    void ResolveEvents();
    void JoinPacketLossCheckerThread();
    bool ResubscribingChannelEvents();

    std::optional<uint64_t> version_;
    std::string channel_id_;
    interface::EventListenerRepository* event_listener_repository_;
    interface::ApiClient* api_;
    Listener* listener_;
    std::mutex event_mtx_;
    std::set<nlohmann::json> queued_events_;
    std::unique_ptr<std::thread> packet_loss_checker_thread_;
    bool packet_loss_checker_canceled_;
    bool disposed_;

public:
    friend class RtcApiEventObserverTest;
};

}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_EVENT_OBSERVER_HPP_ */
