//
//  client.hpp
//  skyway
//
//  Created by sandabu on 2021/11/08.
//  Copyright © 2020 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_CLIENT_HPP_
#define SKYWAY_RTC_API_CLIENT_HPP_

#include <json.hpp>

#include "skyway/core/context_options.hpp"
#include "skyway/model/domain.hpp"
#include "skyway/rtc_api/interface/api_client.hpp"
#include "skyway/rtc_api/interface/channel_state.hpp"
#include "skyway/rtc_api/interface/client.hpp"
#include "skyway/rtc_api/interface/event_listener_repository.hpp"

namespace skyway {
namespace rtc_api {

/// @brief RTC-APIサーバと通信を行うクライアント
class Client : public interface::Client {
public:
    Client(const rpc::RapiOptions& options);

    bool Connect() override;
    std::unique_ptr<interface::ChannelState> CreateChannel(
        const model::Channel::Init& init) override;
    std::unique_ptr<interface::ChannelState> FindOrCreateChannel(
        const model::Channel::Init& init) override;
    std::unique_ptr<interface::ChannelState> FindChannel(
        const model::Channel::Query& query) override;
    bool DeleteChannel(const std::string& channel_id) override;
    bool LeaveChannel(const std::string& channel_id, const std::string& member_id) override;
    bool UpdateChannelMetadata(const std::string& channel_id, const std::string& metadata) override;

    boost::optional<model::Member> JoinChannel(const std::string& channel_id,
                                               const model::Member::Init& init,
                                               const boost::optional<time_t> ttl_sec) override;
    bool UpdateMemberMetadata(const std::string& channel_id,
                              const std::string& member_id,
                              const std::string& metadata) override;
    boost::optional<time_t> GetServerUnixTimeSec() override;
    bool UpdateMemberTtl(const std::string& channel_id,
                         const std::string& member_id,
                         const std::time_t ttl_sec) override;
    bool UpdateAuthToken(const std::string& token) override;
    boost::optional<model::Publication> Publish(const model::Publication::Init& init) override;
    bool UpdatePublicationMetadata(const std::string& channel_id,
                                   const std::string& publication_id,
                                   const std::string& metadata) override;
    bool Unpublish(const std::string& channel_id, const std::string& publication_id) override;
    bool EnablePublication(const std::string& channel_id,
                           const std::string& publication_id) override;
    bool DisablePublication(const std::string& channel_id,
                            const std::string& publication_id) override;
    boost::optional<model::Subscription> Subscribe(const model::Subscription::Init& init) override;
    bool Unsubscribe(const std::string& channel_id, const std::string& subscription_id) override;
    bool EnableSubscription(const std::string& channel_id,
                            const std::string& subscription_id) override;
    bool DisableSubscription(const std::string& channel_id,
                             const std::string& subscription_id) override;

private:
    std::unique_ptr<interface::EventListenerRepository> event_listener_repository_;
    std::unique_ptr<interface::ApiClient> api_;

public:
    friend class RtcApiClientTest;
};

}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_CLIENT_HPP_ */
