//
//  unknown_plugin.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/07/14.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_UNKNOWN_PLUGIN_PLUGIN_HPP_
#define SKYWAY_PLUGIN_UNKNOWN_PLUGIN_PLUGIN_HPP_

#include "skyway/core/interface/remote_member_plugin.hpp"

namespace skyway {
namespace plugin {
namespace unknown_plugin {

/// @brief 機能として対応していないPlugin
class Plugin : public core::interface::RemoteMemberPlugin {
public:
    std::string GetSubtype() const override;
    /// @cond INTERNAL_SECTION
    std::shared_ptr<core::interface::RemoteMember> Create(std::shared_ptr<core::interface::Channel> channel,
                                                          const model::Member& dto) const override;
    /// @endcond
};

}  // namespace unknown_plugin
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_UNKNOWN_PLUGIN_PLUGIN_HPP_ */
