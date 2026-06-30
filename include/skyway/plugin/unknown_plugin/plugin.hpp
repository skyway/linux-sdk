//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_UNKNOWN_PLUGIN_PLUGIN_HPP_
#define SKYWAY_PLUGIN_UNKNOWN_PLUGIN_PLUGIN_HPP_

#include "skyway/core/interface/remote_member_plugin.hpp"

namespace skyway {
namespace plugin {
namespace unknown_plugin {

class Plugin : public core::interface::RemoteMemberPlugin {
public:
    std::string GetSubtype() const override;

    std::shared_ptr<core::interface::RemoteMember> Create(
        std::shared_ptr<core::interface::Channel> channel, const model::Member& dto) const override;
};

}  // namespace unknown_plugin
}  // namespace plugin
}  // namespace skyway

#endif
