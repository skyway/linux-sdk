//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ANALYTICS_CONFIG_HPP_
#define SKYWAY_ANALYTICS_CONFIG_HPP_

namespace skyway {
namespace analytics {
namespace config {

constexpr char kDefaultDomain[] = "analytics-logging.skyway.ntt.com";

constexpr bool kDefaultUseSecureProtocol = true;

constexpr char kApiVersion[] = "v2";

constexpr int kMaxSocketReconnectCount = 8;

constexpr int kSocketOpenTimeoutMillisec = 10 * 1000;

constexpr int kSocketCloseTimeoutMillisec = 10 * 1000;

constexpr int kSocketResendIntervalMillisec = 30 * 1000;
constexpr int kMaxRetryCount                = 6;
constexpr std::chrono::seconds kInitialBackoff{1};
constexpr std::chrono::seconds kMaxBackoff{16};

}  // namespace config
}  // namespace analytics
}  // namespace skyway

#endif
