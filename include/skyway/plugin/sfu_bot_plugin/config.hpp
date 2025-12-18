//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONFIG_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONFIG_HPP_

#include <string>

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace config {

extern const std::string kDefaultSfuApiUrl;
extern const bool kDefaultSfuUseSecureProtocol;
extern const int kDefaultSfuApiVersion;
extern const std::string kSubtype;
extern const int kDefaultMaxSubscribers;
extern const int kDefaultMaxRestartIceCount;
extern const int kDefaultRestartIceCheckingTimeSec;

}  // namespace config
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_CONFIG_HPP_ */
