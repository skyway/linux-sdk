//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_FORWARDING_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_FORWARDING_HPP_

#include "skyway/core/interface/publication.hpp"
#include "skyway/plugin/sfu_bot_plugin/config.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {

struct ForwardingConfigure {
    int max_subscribers = config::kDefaultMaxSubscribers;
};

enum class ForwardingState { kStarted, kStopped };

class Forwarding : public core::interface::Publication::EventListener {
public:
    class EventListener {
    public:
        virtual void OnStopped() {}
    };

    Forwarding(const std::string& id,
               const ForwardingConfigure& configure,
               std::shared_ptr<core::interface::Publication> relaying_publication,
               const std::string& identifier_key);
    ~Forwarding();

    void AddEventListener(EventListener* listener);

    void RemoveEventListener(EventListener* listener);

    void Stop();

    ForwardingState State();

    std::string Id();

    ForwardingConfigure Configure() const;

    std::shared_ptr<core::interface::Publication> OriginPublication() const;

    std::shared_ptr<core::interface::Publication> RelayingPublication();

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

#endif
