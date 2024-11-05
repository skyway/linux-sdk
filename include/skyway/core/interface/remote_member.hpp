//
//  remote_member.hpp
//  skyway
//
//  Created by sandabu on 2021/12/21.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_HPP_
#define SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_HPP_

#include <unordered_map>

#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/stream.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class Channel;

using LocalPersonId  = std::string;
using SubscriptionId = std::string;

/// @brief このSDK以外で生成されたメンバ
/// @details RemoteMemberはRemoteMemberPluginを利用して振る舞いを変更します。
/// MemberのSubtypeに応じて登録されているPluginを利用し、存在しない場合は`UnknownPlugin`で初期化されます。
class RemoteMember : public Member {
public:
    virtual ~RemoteMember() = default;

    /// @cond INTERNAL_SECTION
    /// @brief 破棄処理を行います。
    /// @details このAPIはlibskyway内部で利用される関数であり、ラップしないでください。
    virtual void Dispose() {};

    /// @brief LocalPersonのPublicationがSubscribeされた時にコールされる関数
    /// @details このAPIはlibskyway内部で利用される関数であり、ラップしないでください。
    /// @param publication Publication
    /// @param subscription_id SubscriptionのID
    virtual void OnSubscribedLocalPersonsPublication(Publication* publication,
                                                     const SubscriptionId& subscription_id) {};

    /// @brief LocalPersonのPublicationがUnsubscribeされた時にコールされる関数
    /// @details このAPIはlibskyway内部で利用される関数であり、ラップしないでください。
    /// @param publication Publication
    virtual void OnUnsubscribedLocalPersonsPublication(Publication* publication) {};

    /// @brief LocalPersonがSubscribeした時にコールされる関数
    /// @details このAPIはlibskyway内部で利用される関数であり、ラップしないでください。
    /// @param subscription Subscription
    virtual void OnLocalPersonSubscribed(Subscription* subscription) {};

    /// @brief LocalPersonがUnsubscribeした時にコールされる関数
    /// @details このAPIはlibskyway内部で利用される関数であり、ラップしないでください。
    /// @param subscription Subscription
    virtual void OnLocalPersonUnsubscribed(Subscription* subscription) {};
    /// @endcond

protected:
    RemoteMember(Channel* channel, const model::Member& dto);
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_HPP_ */
