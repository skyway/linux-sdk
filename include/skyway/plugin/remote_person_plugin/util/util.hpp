//
//  util.hpp
//  skyway
//
//  Created by Muranaka Kei on 2024/09/18.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_UTIL_CONFIG_HPP_
#define SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_UTIL_CONFIG_HPP_

#include <api/stats/rtc_stats_report.h>

#include <json.hpp>

namespace skyway {
namespace plugin {
namespace remote_person {
namespace connection {
namespace util {

const std::optional<nlohmann::json> StatsToJson(
    const rtc::scoped_refptr<const webrtc::RTCStatsReport>& report);

}  // namespace util
}  // namespace connection
}  // namespace remote_person
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_REMOTE_PERSON_PLUGIN_UTIL_CONFIG_HPP_ */
