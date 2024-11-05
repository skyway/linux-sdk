//
//  transport_repository.hpp
//  skyway
//
//  Created by iorar on 2023/10/10.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_REPOSITORY_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_REPOSITORY_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/device.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/recv_transport.hpp"
#include "skyway/plugin/sfu_bot_plugin/interface/send_transport.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

using LocalPersonId = std::string;

/// @brief PeerConnectionを多重化するためのmediasoup transportを管理するリポジトリ
///
/// @details
/// ブラウザ側でPeerConnectionが500個を超えるとガベージコレクションが走らず、正常にPeerConnectionが生成できない問題があるため、多重化をしています。
///
/// SFUサーバでは、PublisherIdまたはSubscriberIdをキーにTransportを多重化しており、このクラスではTransportを使い回すため保存しています。
class TransportRepository {
public:
    virtual ~TransportRepository() = default;

    /// Deviceがロード済みか返します。
    virtual bool IsDeviceLoaded() = 0;

    /// Deviceをロードします。
    virtual bool LoadDevice(nlohmann::json caps, const Device::PeerConnectionOptions* options) = 0;

    /// @brief RtpCapabilitiesを返します。
    /// @details この関数をコールする前に`LoadDevice`をコールする必要があります。
    virtual nlohmann::json GetRtpCapabilities() = 0;

    /// @brief SendTransportを作成し、Repositoryに保存します。
    /// @param analytics_client Analyticsクライアント
    /// @param transport_options Transportオプション
    /// @param pc_options PeerConnectionオプション
    /// @param local_person_id LocalPersonID
    virtual SendTransport* CreateSendTransport(
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) = 0;

    /// @brief RecvTransportを作成し、Repositoryに保存します。
    /// @param analytics_client Analyticsクライアント
    /// @param transport_options Transportオプション
    /// @param pc_options PeerConnectionオプション
    /// @param local_person_id LocalPersonID
    virtual RecvTransport* CreateRecvTransport(
        analytics::interface::AnalyticsClient* analytics_client,
        const nlohmann::json& transport_options,
        const Device::PeerConnectionOptions* pc_options,
        const LocalPersonId& local_person_id) = 0;

    /// @brief SendTransportを取得します。
    /// @param transport_id Transport ID
    virtual SendTransport* GetSendTransport(const LocalPersonId& local_person_id,
                                            const std::string& transport_id) = 0;

    /// @brief RecvTransportを取得します。
    /// @param transport_id Transport ID
    virtual RecvTransport* GetRecvTransport(const LocalPersonId& local_person_id,
                                            const std::string& transport_id) = 0;

    /// @brief リポジトリのリソース(transport etc.)を削除します。
    /// @param local_person_id トランスポートに紐づくLocalPersonID
    virtual void RemoveResources(const LocalPersonId& local_person_id) = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_REPOSITORY_HPP_ */
