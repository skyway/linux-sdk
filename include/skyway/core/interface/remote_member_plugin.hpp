//
//  remote_member_plugin.hpp
//  skyway
//
//  Created by sandabu on 2021/12/17.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_PLUGIN_HPP_
#define SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_PLUGIN_HPP_

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/remote_member.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class RemoteMemberPlugin {
public:
    virtual ~RemoteMemberPlugin() = default;
    /// @brief Pluginのサブタイプ
    virtual std::string GetSubtype() const = 0;
    /// @cond INTERNAL_SECTION
    virtual std::shared_ptr<RemoteMember> Create(std::shared_ptr<interface::Channel> channel,
                                                 const model::Member& dto) const = 0;
    virtual void OnLocalPersonDisposed(const std::string& local_person_id) {}
    /// @endcond
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_REMOTE_MEMBER_PLUGIN_HPP_ */
