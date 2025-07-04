//
//  receiver.hpp
//  skyway
//
//  Created by salmon on 2022/1/25.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECEIVER_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECEIVER_HPP_

#include <atomic>
#include <mediasoupclient.hpp>
#include <unordered_map>

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/remote_stream.hpp"
#include "skyway/core/interface/subscription.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/transport_repository.hpp"
#include "skyway/plugin/sfu_bot_plugin/sfu_api_client.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace connection {

using RemoteStreamInterface = core::interface::RemoteStream;

class Receiver : public mediasoupclient::Consumer::Listener,
                 public core::interface::Subscription::InternalListener,
                 public core::interface::Subscription::Callback {
public:
    Receiver(const std::string& local_person_id,
             const std::string& bot_id,
             interface::SfuApiClient* client,
             interface::TransportRepository* transport_repo,
             std::shared_ptr<core::interface::Subscription> subscription,
             analytics::interface::AnalyticsClient* analytics_client);

    ~Receiver();
    void StartReceiving(const interface::Device::PeerConnectionOptions* pc_options);
    bool StopReceiving();

    // mediasoupclient::Consumer::Listener
    void OnTransportClose(mediasoupclient::Consumer* consumer) override;

    // core::interface::Subscription::InternalListener
    void OnChangePreferredEncoding(std::shared_ptr<core::interface::Subscription> subscription) override;

    // core::interface::Subscription::Callback
    const std::optional<nlohmann::json> GetStatsReport(
            std::shared_ptr<core::interface::Subscription> subscription) override;

private:
    bool LoadDevice(const std::string& publication_id,
                    const std::string& origin_publication_id,
                    const interface::Device::PeerConnectionOptions* pc_options);
    std::optional<dto::CreateConsumerResponse> CreateConsumer(
        const std::string& publication_id, const std::string& origin_publication_id);
    std::shared_ptr<RemoteStreamInterface> Consume(const std::string& producer_id,
                                                   nlohmann::json consumer_options);
    int GetLayerIndex(const std::string& preferred_encoding_id,
                      std::vector<model::Encoding> encodings);
    skyway::plugin::sfu_bot::interface::RecvTransport* GetOrCreateRecvTransport(
        const std::string& transport_id,
        std::optional<nlohmann::json>,
        const interface::Device::PeerConnectionOptions* pc_options);

    void SetupTransportAccessForStream();
    void CreateConsumeThread(const std::string& publication_id, const std::string& origin_publication_id, const interface::Device::PeerConnectionOptions* pc_options);

    std::string local_person_id_;
    std::string bot_id_;
    interface::SfuApiClient* client_;
    interface::TransportRepository* transport_repo_;

    std::weak_ptr<core::interface::Subscription> subscription_;

    analytics::interface::AnalyticsClient* analytics_client_;

    interface::RecvTransport* transport_ = nullptr;
    ConsumerId consumer_id_;

    std::mutex receive_threads_mtx_;
    std::vector<std::unique_ptr<std::thread>> receive_threads_;

public:
    friend class SfuBotPluginReceiverTest;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECEIVER_HPP_ */
