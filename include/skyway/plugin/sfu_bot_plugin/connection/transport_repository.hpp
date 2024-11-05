//
//  transport_repository.hpp
//  skyway
//
//  Created by sandabu on 2022/06/27.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_TRANSPORT_REPOSITORY_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_TRANSPORT_REPOSITORY_HPP_

#include <mediasoupclient.hpp>

#include "skyway/core/connection_state.hpp"
#include "skyway/plugin/sfu_bot_plugin/config.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/sfu_api_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport_repository.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

class SfuIntegrationTest;

namespace connection {

using LocalPersonId   = std::string;
using ConnectionState = std::string;

class TransportRepository : public interface::TransportRepository {
public:
    /// コンストラクタ
    TransportRepository(interface::SfuApiClient* client);

    /// デストラクタ
    ~TransportRepository();

    bool IsDeviceLoaded() override;

    bool LoadDevice(nlohmann::json caps,
                    const interface::Device::PeerConnectionOptions* options) override;

    nlohmann::json GetRtpCapabilities() override;

    interface::SendTransport* CreateSendTransport(
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const interface::Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) override;

    interface::RecvTransport* CreateRecvTransport(
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const interface::Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) override;

    interface::SendTransport* GetSendTransport(const LocalPersonId& local_person_id,
                                               const std::string& transport_id) override;

    interface::RecvTransport* GetRecvTransport(const LocalPersonId& local_person_id,
                                               const std::string& transport_id) override;

    void RemoveResources(const LocalPersonId& local_person_id) override;

private:
    TransportRepository(interface::SfuApiClient* client, std::unique_ptr<interface::Device> device);
    bool ApplyCodecCapabilities(std::vector<model::Codec> publication_codec_caps,
                                nlohmann::json& router_rtp_capabilities);

    interface::SfuApiClient* client_;
    std::mutex device_mtx_;
    std::unique_ptr<interface::Device> device_;

    // Transports are managed with multi composite primary key(LocalPersonID and TransportID)
    std::mutex send_transports_mtx_;
    std::unordered_multimap<LocalPersonId, std::unique_ptr<interface::SendTransport>>
        send_transports_;
    std::mutex recv_transports_mtx_;
    std::unordered_multimap<LocalPersonId, std::unique_ptr<interface::RecvTransport>>
        recv_transports_;

public:
    friend class skyway::plugin::sfu_bot::SfuIntegrationTest;
    friend class SfuBotPluginTransportRepositoryTest;
    friend class SfuBotPluginSenderTest;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_TRANSPORT_REPOSITORY_HPP_ */
