//
//  connection.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/08/04.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_CONNECTION_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_CONNECTION_HPP_

#include "skyway/core/interface/subscription.hpp"
#include "skyway/plugin/sfu_bot_plugin/forwarding.hpp"

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

struct StartForwardingResult {
    std::string forwarding_id;
    std::string identifier_key;
};

class SfuConnection {
public:
    virtual ~SfuConnection() = default;
    virtual std::optional<StartForwardingResult> StartForwarding(
        std::shared_ptr<core::interface::Publication> publication,
        ForwardingConfigure configure)                                                       = 0;
    virtual bool StopForwarding(Forwarding* forwarding, bool with_api_request)               = 0;
    virtual void StartReceiving(std::shared_ptr<core::interface::Subscription> subscription) = 0;
    virtual bool StopReceiving(const std::string& subscription_id)                           = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_SFU_CONNECTION_HPP_ */
