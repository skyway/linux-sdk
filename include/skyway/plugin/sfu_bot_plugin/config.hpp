//
//  config.hpp
//  skyway
//
//  Created by salmon on 2022/2/22.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONFIG_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONFIG_HPP_

#include <string>

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace config {

extern const std::string DEFAULT_SFU_API_URL;
extern const bool DEFAULT_SFU_USE_SECURE_PROTOCOL;
extern const int DEFAULT_SFU_API_VERSION;
extern const std::string SUBTYPE;
extern const int DEFAULT_MAX_SUBSCRIBERS;
extern const int DEFAULT_MAX_RESTART_ICE_COUNT;
extern const int DEFAULT_RESTART_ICE_CHECKING_TIME_SEC;

}  // namespace config
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONFIG_HPP_ */
