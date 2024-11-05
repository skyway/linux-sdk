//
//  plugin.hpp
//  skyway
//
//  Created by sandabu on 2021/12/21.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_PLUGIN_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_PLUGIN_HPP_

#include <api/peer_connection_interface.h>

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/remote_member_plugin.hpp"

namespace skyway {
namespace plugin {
namespace remote_person {

using PluginInterface       = core::interface::RemoteMemberPlugin;
using RemoteMemberInterface = core::interface::RemoteMember;
using ChannelInterface      = core::interface::Channel;

/// @brief RemotePersonのPlugin
class Plugin : public PluginInterface {
public:
    Plugin(rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory);
    std::string GetSubtype() const override;
    /// @cond INTERNAL_SECTION
    std::unique_ptr<RemoteMemberInterface> Create(ChannelInterface* channel,
                                                  const model::Member& member_dto) const override;
    /// @endcond

private:
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
};

}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_PLUGIN_HPP_ */
