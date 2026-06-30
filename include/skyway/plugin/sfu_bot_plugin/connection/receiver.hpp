//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECEIVER_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONNECTION_RECEIVER_HPP_

#include <Consumer.hpp>
#include <atomic>
#include <optional>

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
                 public core::interface::Subscription::Callback,
                 public std::enable_shared_from_this<Receiver> {
public:
    Receiver(const std::string& local_person_id,
             const std::string& bot_id,
             interface::SfuApiClient* client,
             interface::TransportRepository* transport_repo,
             std::shared_ptr<core::interface::Subscription> subscription);

    ~Receiver();
    bool StartReceiving(const interface::Device::PeerConnectionOptions* pc_options);
    bool StopReceiving();
    void Dispose();

    void OnTransportClose(mediasoupclient::Consumer* consumer) override;

    void OnChangePreferredEncoding(
        std::shared_ptr<core::interface::Subscription> subscription) override;

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
    std::shared_ptr<interface::RecvTransport> AcquireRecvTransport(
        const std::string& transport_id,
        std::optional<nlohmann::json> transport_options,
        const interface::Device::PeerConnectionOptions* pc_options);
    std::shared_ptr<interface::RecvTransport> GetRecvTransport();
    void SetupTransportAccessForStream();
    void CreateConsumeThread(const std::string& publication_id,
                             const std::string& origin_publication_id,
                             const interface::Device::PeerConnectionOptions* pc_options);

    std::string local_person_id_;
    std::string bot_id_;
    interface::SfuApiClient* client_;
    interface::TransportRepository* transport_repo_;

    std::weak_ptr<core::interface::Subscription> subscription_;

    std::optional<std::string> transport_id_;
    ConsumerId consumer_id_;
    std::atomic<bool> is_disposed_ = false;

    std::mutex receive_threads_mtx_;
    std::vector<std::unique_ptr<std::thread>> receive_threads_;

public:
    friend class SfuBotPluginReceiverTest;
};

}  // namespace connection
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif
