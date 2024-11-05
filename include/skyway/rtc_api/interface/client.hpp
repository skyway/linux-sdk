//
//  client.hpp
//  skyway
//
//  Created by sandabu on 2022/06/23.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_INTERFACE_CLIENT_HPP_
#define SKYWAY_RTC_API_INTERFACE_CLIENT_HPP_

#include "skyway/rtc_api/channel_state.hpp"

namespace skyway {
namespace rtc_api {
namespace interface {

/// @brief RTC-APIサーバと通信を行うクライアント
class Client {
public:
    virtual ~Client() = default;
    /// @brief RTC-APIサーバに接続します。
    ///
    /// RTC APIサーバへの操作は最初にこのメソッドを呼ぶ必要があります。
    virtual bool Connect() = 0;
    /// @brief Channelを作成します。
    virtual std::unique_ptr<ChannelState> CreateChannel(const model::Channel::Init& init)       = 0;
    virtual std::unique_ptr<ChannelState> FindChannel(const model::Channel::Query& query)       = 0;
    virtual std::unique_ptr<ChannelState> FindOrCreateChannel(const model::Channel::Init& init) = 0;
    virtual bool DeleteChannel(const std::string& channel_id)                                   = 0;
    virtual bool LeaveChannel(const std::string& channel_id, const std::string& member_id)      = 0;
    virtual bool UpdateChannelMetadata(const std::string& channel_id,
                                       const std::string& metadata)                             = 0;

    virtual boost::optional<model::Member> JoinChannel(const std::string& channel_id,
                                                       const model::Member::Init& init,
                                                       const boost::optional<time_t> ttl_sec) = 0;
    virtual bool UpdateMemberMetadata(const std::string& channel_id,
                                      const std::string& member_id,
                                      const std::string& metadata)                            = 0;
    virtual boost::optional<time_t> GetServerUnixTimeSec()                                       = 0;
    virtual bool UpdateMemberTtl(const std::string& channel_id,
                                 const std::string& member_id,
                                 const std::time_t ttl_sec)                                   = 0;
    virtual bool UpdateAuthToken(const std::string& token)                                    = 0;
    virtual boost::optional<model::Publication> Publish(const model::Publication::Init& init) = 0;
    virtual bool UpdatePublicationMetadata(const std::string& channel_id,
                                           const std::string& publication_id,
                                           const std::string& metadata)                       = 0;
    virtual bool Unpublish(const std::string& channel_id, const std::string& publication_id)  = 0;
    virtual bool EnablePublication(const std::string& channel_id,
                                   const std::string& publication_id)                         = 0;
    virtual bool DisablePublication(const std::string& channel_id,
                                    const std::string& publication_id)                        = 0;
    virtual boost::optional<model::Subscription> Subscribe(
        const model::Subscription::Init& init)                                                  = 0;
    virtual bool Unsubscribe(const std::string& channel_id, const std::string& subscription_id) = 0;
    virtual bool EnableSubscription(const std::string& channel_id,
                                    const std::string& subscription_id)                         = 0;
    virtual bool DisableSubscription(const std::string& channel_id,
                                     const std::string& subscription_id)                        = 0;
};

}  // namespace interface
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_INTERFACE_CLIENT_HPP_ */
