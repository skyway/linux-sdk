//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_GLOBAL_CONFIG_HPP_
#define SKYWAY_GLOBAL_CONFIG_HPP_

namespace skyway {
namespace global {
namespace config {

extern const int kDefaultTimeoutSec;
extern const int kDefaultTimeoutMs;
extern const int kMaxThreadNameSize;

constexpr int kLocalSleepIntervalMs = 1;
constexpr int kNetworkSleepIntervalMs = 10;

}  // namespace config
}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_CONFIG_HPP_ */
