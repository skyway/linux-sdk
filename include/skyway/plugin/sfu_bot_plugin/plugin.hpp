//
//  plugin.hpp
//  skyway
//
//  Created by salmon on 2022/1/25.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_PLUGIN_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_PLUGIN_HPP_

#include <api/peer_connection_interface.h>

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/remote_member_plugin.hpp"
#include "skyway/network/interface/http_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport_repository.hpp"
#include "skyway/plugin/sfu_bot_plugin/sfu_bot.hpp"
#include "skyway/plugin/sfu_bot_plugin/sfu_options.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

using PluginInterface       = core::interface::RemoteMemberPlugin;
using MemberInterface       = core::interface::Member;
using RemoteMemberInterface = core::interface::RemoteMember;
using ChannelInterface      = core::interface::Channel;
using HttpClientInterface   = network::interface::HttpClient;

/// @brief SfuBotのPlugin
class Plugin : public PluginInterface {
public:
    Plugin(HttpClientInterface* http,
           rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
           sfu_options::SfuOptionsParams sfu_options);
    std::string GetSubtype() const override;
    /// @cond INTERNAL_SECTION
    std::unique_ptr<RemoteMemberInterface> Create(ChannelInterface* channel,
                                                  const model::Member& member_dto) const override;
    /// @endcond
    /// @brief SFUBotを作成します。
    SfuBot* CreateBot(ChannelInterface* channel);
    /// @brief SFUBotを削除します。
    bool DeleteBot(SfuBot* sfu_bot);

    // PluginInterface
    void OnLocalPersonDisposed(const std::string& local_person_id) override;

private:
    class BotCreationListener : public ChannelInterface::EventListener {
    public:
        SfuBot* WaitForBotCreation(const std::string& bot_id);

    private:
        // Impl ChannelEventListener
        void OnMemberJoined(MemberInterface* member) override;
        std::mutex candidate_bots_mtx_;
        std::vector<SfuBot*> candidate_bots_;
    };

    std::unique_ptr<interface::SfuApiClient> client_;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory_;
    std::unique_ptr<interface::TransportRepository> transport_repo_;

    std::mutex create_bot_mtx_;

public:
    /// @cond INTERNAL_SECTION
    friend class SfuIntegrationTest;
    /// @endcond
};

}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_PLUGIN_HPP_ */
