//
//  plugin.hpp
//  skyway
//
//  Created by salmon on 2022/1/25.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.
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
using HttpClientInterface   = network::interface::HttpClient;

/// @brief SfuBotのPlugin
class Plugin : public PluginInterface {
public:
    Plugin(HttpClientInterface* http,
           rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory,
           sfu_options::SfuOptionsParams sfu_options);
    std::string GetSubtype() const override;
    /// @cond INTERNAL_SECTION
    std::shared_ptr<core::interface::RemoteMember> Create(std::shared_ptr<core::interface::Channel> channel,
                                                  const model::Member& member_dto) const override;
    /// @endcond
    /// @brief SFUBotを作成します。
    std::shared_ptr<SfuBot> CreateBot(std::shared_ptr<core::interface::Channel> channel);
    /// @brief SFUBotを削除します。
    bool DeleteBot(std::shared_ptr<SfuBot> sfu_bot);

    // PluginInterface
    void OnLocalPersonDisposed(const std::string& local_person_id) override;

private:
    class BotCreationListener : public core::interface::Channel::EventListener {
    public:
        std::shared_ptr<SfuBot> WaitForBotCreation(const std::string& bot_id);

    private:
        // Impl ChannelEventListener
        void OnMemberJoined(std::shared_ptr<core::interface::Member> member) override;
        std::mutex candidate_bots_mtx_;
        std::vector<std::weak_ptr<SfuBot>> candidate_bots_;
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
