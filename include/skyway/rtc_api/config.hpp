//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_RTC_API_CONFIG_HPP_
#define SKYWAY_RTC_API_CONFIG_HPP_

#include <string>

namespace skyway {
namespace rtc_api {
namespace config {

extern const std::string kJsonRpcVersion;
extern const std::string kDefaultRapiDomain;
extern const bool kDefaultSecure;
extern const int kMaxRetryConnect;
extern const int kWaitingTimeForConnect;
extern const int kWaitingTimeForPacket;
extern const int kMaxRetrySend;
extern const int kDefaultTimeoutForSend;

}  // namespace config
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_CONFIG_HPP_ */
