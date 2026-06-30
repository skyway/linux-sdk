//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_TRANSPORT_REPOSITORY_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_TRANSPORT_REPOSITORY_HPP_

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
    TransportRepository(interface::SfuApiClient* client);

    ~TransportRepository();

    bool IsDeviceLoaded() override;

    bool LoadDevice(nlohmann::json caps,
                    const interface::Device::PeerConnectionOptions* options) override;

    nlohmann::json GetRtpCapabilities() override;

    std::shared_ptr<interface::SendTransport> CreateSendTransport(
        const nlohmann::json& transport_options,
        const interface::Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) override;

    std::shared_ptr<interface::RecvTransport> CreateRecvTransport(
        const nlohmann::json& transport_options,
        const interface::Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) override;

    std::shared_ptr<interface::SendTransport> GetSendTransport(
        const LocalPersonId& local_person_id, const std::string& transport_id) override;

    std::shared_ptr<interface::RecvTransport> GetRecvTransport(
        const LocalPersonId& local_person_id, const std::string& transport_id) override;

    void RemoveResources(const LocalPersonId& local_person_id) override;

private:
    TransportRepository(interface::SfuApiClient* client, std::unique_ptr<interface::Device> device);
    bool ApplyCodecCapabilities(std::vector<model::Codec> publication_codec_caps,
                                nlohmann::json& router_rtp_capabilities);

    interface::SfuApiClient* client_;
    std::mutex device_mtx_;
    std::unique_ptr<interface::Device> device_;

    std::mutex send_transports_mtx_;
    std::unordered_multimap<LocalPersonId, std::shared_ptr<interface::SendTransport>>
        send_transports_;
    std::mutex recv_transports_mtx_;
    std::unordered_multimap<LocalPersonId, std::shared_ptr<interface::RecvTransport>>
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

#endif
