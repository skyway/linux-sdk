//
//  api_client.hpp
//  skyway
//
//  Created by sandabu on 2022/01/06.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_RPC_API_CLIENT_HPP_
#define SKYWAY_RTC_API_RPC_API_CLIENT_HPP_

#include <atomic>
#include <boost/optional.hpp>
#include <mutex>

#include "skyway/core/context_options.hpp"
#include "skyway/rtc_api/interface/api_client.hpp"
#include "skyway/rtc_api/interface/rpc.hpp"
#include "skyway/rtc_api/rpc/dto/message.hpp"

namespace skyway {
namespace rtc_api {
namespace rpc {

using ApiClientInterface        = interface::ApiClient;
using AuthTokenManagerInterface = token::interface::AuthTokenManager;
using RapiOptions               = core::ContextOptions::RtcApi;

class ApiClient : public ApiClientInterface {
public:
    ApiClient(AuthTokenManagerInterface* auth,
              std::unique_ptr<interface::Rpc> rpc,
              const RapiOptions& options);
    ~ApiClient();

    bool Connect() override;

    boost::optional<dto::CreateChannelResult> CreateChannel(
        const model::Channel::Init& init) override;

    boost::optional<model::Channel> FindOrCreateChannel(const model::Channel::Init& init) override;

    boost::optional<model::Channel> GetChannel(const std::string& channel_id) override;
    boost::optional<model::Channel> GetChannelByName(const std::string& name) override;
    bool DeleteChannel(const std::string& channel_id) override;
    bool UpdateChannelMetadata(const std::string& channel_id, const std::string& metadata) override;
    boost::optional<dto::JoinChannelResult> AddMember(
        const std::string& channel_id,
        const model::Member::Init& init,
        const boost::optional<time_t> ttl_sec) override;
    bool RemoveMember(const std::string& channel_id, const std::string& member_id) override;
    bool UpdateMemberMetadata(const std::string& channel_id,
                              const std::string& member_id,
                              const std::string& metadata) override;
    boost::optional<time_t> GetServerUnixTimeSec() override;
    bool UpdateMemberTtl(const std::string& channel_id,
                         const std::string& member_id,
                         const std::time_t ttl_sec) override;
    bool UpdateAuthToken(const std::string& token) override;
    boost::optional<dto::PublishStreamResult> PublishStream(
        const model::Publication::Init& init) override;
    bool UpdatePublicationMetadata(const std::string& channel_id,
                                   const std::string& publication_id,
                                   const std::string& metadata) override;
    bool UnpublishStream(const std::string& channel_id, const std::string& publication_id) override;
    bool EnablePublication(const std::string& channel_id,
                           const std::string& publication_id) override;
    bool DisablePublication(const std::string& channel_id,
                            const std::string& publication_id) override;
    boost::optional<dto::SubscribeStreamResult> SubscribeStream(
        const model::Subscription::Init& init) override;
    bool UnsubscribeStream(const std::string& channel_id,
                           const std::string& subscription_id) override;
    bool EnableSubscription(const std::string& channel_id,
                            const std::string& subscription_id) override;
    bool DisableSubscription(const std::string& channel_id,
                             const std::string& subscription_id) override;

    bool SubscribeChannelEvents(const std::string& channel_id, uint64_t offset) override;

private:
    template <class Result>
    // If error occured, `error` will be set and return boost::none
    boost::optional<Result> Request(const std::string& method,
                                    nlohmann::json& params,
                                    dto::ResponseErrorMessage* error);
    RapiOptions options_;
    AuthTokenManagerInterface* auth_;
    std::unique_ptr<interface::Rpc> rpc_;
    std::atomic<bool> is_disposed_;

public:
    friend class RtcApiRpcApiClientTest;
};

}  // namespace rpc
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_RPC_API_CLIENT_HPP_ */
