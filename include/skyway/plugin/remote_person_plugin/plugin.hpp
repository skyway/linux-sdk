//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
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

/// @brief RemotePersonのPlugin
class Plugin : public PluginInterface {
public:
    Plugin(rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory);
    std::string GetSubtype() const override;
    /// @cond INTERNAL_SECTION
    std::shared_ptr<core::interface::RemoteMember> Create(std::shared_ptr<core::interface::Channel> channel,
                                                  const model::Member& member_dto) const override;
    /// @endcond

private:
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
};

}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_PLUGIN_HPP_ */
