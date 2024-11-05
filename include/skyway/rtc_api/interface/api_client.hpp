//
//  api_client.hpp
//  skyway
//
//  Created by sandabu on 2022/06/21.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_INTERFACE_API_CLIENT_HPP_
#define SKYWAY_RTC_API_INTERFACE_API_CLIENT_HPP_

#include <boost/optional.hpp>
#include <json.hpp>

#include "skyway/rtc_api/rpc/dto/result.hpp"

namespace skyway {
namespace rtc_api {
namespace interface {

/// JSON-RPCモジュール
class ApiClient {
public:
    virtual ~ApiClient()   = default;
    virtual bool Connect() = 0;

    virtual boost::optional<rpc::dto::CreateChannelResult> CreateChannel(
        const model::Channel::Init& init) = 0;

    virtual boost::optional<model::Channel> FindOrCreateChannel(
        const model::Channel::Init& init) = 0;

    virtual boost::optional<model::Channel> GetChannel(const std::string& channel_id) = 0;
    virtual boost::optional<model::Channel> GetChannelByName(const std::string& name) = 0;
    virtual bool DeleteChannel(const std::string& channel_id)                         = 0;
    virtual bool UpdateChannelMetadata(const std::string& channel_id,
                                       const std::string& metadata)                   = 0;
    virtual boost::optional<rpc::dto::JoinChannelResult> AddMember(
        const std::string& channel_id,
        const model::Member::Init& init,
        const boost::optional<time_t> ttl_sec)                                             = 0;
    virtual bool RemoveMember(const std::string& channel_id, const std::string& member_id) = 0;
    virtual bool UpdateMemberMetadata(const std::string& channel_id,
                                      const std::string& member_id,
                                      const std::string& metadata)                         = 0;
    virtual boost::optional<time_t> GetServerUnixTimeSec()                                    = 0;
    virtual bool UpdateMemberTtl(const std::string& channel_id,
                                 const std::string& member_id,
                                 const std::time_t ttl_sec)                                = 0;
    virtual bool UpdateAuthToken(const std::string& token)                                 = 0;
    virtual boost::optional<rpc::dto::PublishStreamResult> PublishStream(
        const model::Publication::Init& init)                           = 0;
    virtual bool UpdatePublicationMetadata(const std::string& channel_id,
                                           const std::string& publication_id,
                                           const std::string& metadata) = 0;
    virtual bool UnpublishStream(const std::string& channel_id,
                                 const std::string& publication_id)     = 0;
    virtual bool EnablePublication(const std::string& channel_id,
                                   const std::string& publication_id)   = 0;
    virtual bool DisablePublication(const std::string& channel_id,
                                    const std::string& publication_id)  = 0;
    virtual boost::optional<rpc::dto::SubscribeStreamResult> SubscribeStream(
        const model::Subscription::Init& init)                                          = 0;
    virtual bool UnsubscribeStream(const std::string& channel_id,
                                   const std::string& subscription_id)                  = 0;
    virtual bool EnableSubscription(const std::string& channel_id,
                                    const std::string& subscription_id)                 = 0;
    virtual bool DisableSubscription(const std::string& channel_id,
                                     const std::string& subscription_id)                = 0;
    virtual bool SubscribeChannelEvents(const std::string& channel_id, uint64_t offset) = 0;
};

}  // namespace interface
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_INTERFACE_API_CLIENT_HPP_ */
