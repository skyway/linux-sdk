//
//  forwarding.hpp
//  skyway
//
//  Created by salmon on 2022/2/23.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_FORWARDING_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_FORWARDING_HPP_

#include "skyway/core/interface/publication.hpp"
#include "skyway/plugin/sfu_bot_plugin/config.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

// Defined as an outer class to avoid name collisions with member variables.
/// @brief Fowardingの設定
struct ForwardingConfigure {
    /// @brief FowardingをSubscribe出来る最大人数
    int max_subscribers = config::DEFAULT_MAX_SUBSCRIBERS;
};

enum class ForwardingState { kStarted, kStopped };

/// @brief SFUBotが扱うForwarding
class Forwarding : public core::interface::Publication::EventListener {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        /// @brief Forwardingが停止されたときに発生するイベント
        virtual void OnStopped() {}
    };

    Forwarding(const std::string& id,
               const ForwardingConfigure& configure,
               std::shared_ptr<core::interface::Publication> relaying_publication,
               const std::string& identifier_key);
    ~Forwarding();
    /// @brief イベントを購読します。
    void AddEventListener(EventListener* listener);
    /// @brief イベントの購読を中止します。
    void RemoveEventListener(EventListener* listener);
    // Do not wrap Stop() in bridge.
    /// @cond INTERNAL_SECTION
    void Stop();
    /// @endcond

    /// @brief 状態を取得します。
    ForwardingState State();
    /// @brief IDを取得します。
    std::string Id();
    /// @brief ForwardingConfigureを取得します。
    ForwardingConfigure Configure() const;
    /// @brief OriginPublicationを取得します。
    std::shared_ptr<core::interface::Publication> OriginPublication() const;
    /// @brief RelayingPublicationを取得します。
    std::shared_ptr<core::interface::Publication> RelayingPublication();
    /// @brief IdentifierKeyを取得します。
    std::string IdentifierKey();

private:
    void OnUnpublished();

    std::string id_;
    std::unordered_set<EventListener*> listeners_;
    ForwardingConfigure configure_;
    std::weak_ptr<core::interface::Publication> relaying_publication_;
    std::string identifier_key_;
    ForwardingState state_;
};

}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_FORWARDING_HPP_ */
