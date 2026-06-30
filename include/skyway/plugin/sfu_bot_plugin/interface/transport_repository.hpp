//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_REPOSITORY_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_REPOSITORY_HPP_

#include <memory>
#include <string>

#include "skyway/plugin/sfu_bot_plugin/interface/device.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/recv_transport.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/send_transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

using LocalPersonId = std::string;

class TransportRepository {
public:
    virtual ~TransportRepository() = default;

    virtual bool IsDeviceLoaded() = 0;

    virtual bool LoadDevice(nlohmann::json caps, const Device::PeerConnectionOptions* options) = 0;

    virtual nlohmann::json GetRtpCapabilities() = 0;

    virtual std::shared_ptr<SendTransport> CreateSendTransport(
        const nlohmann::json& transport_options,
        const Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) = 0;

    virtual std::shared_ptr<RecvTransport> CreateRecvTransport(
        const nlohmann::json& transport_options,
        const Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) = 0;

    virtual std::shared_ptr<SendTransport> GetSendTransport(const LocalPersonId& local_person_id,
                                                            const std::string& transport_id) = 0;

    virtual std::shared_ptr<RecvTransport> GetRecvTransport(const LocalPersonId& local_person_id,
                                                            const std::string& transport_id) = 0;

    virtual void RemoveResources(const LocalPersonId& local_person_id) = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif
