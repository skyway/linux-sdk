//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_CONFIG_HPP_
#define SKYWAY_SIGNALING_CONFIG_HPP_

#include <string>

namespace skyway {
namespace signaling {
namespace config {

extern const std::string kDefaultDomain;

extern const bool kDefaultUseSecureProtocol;

extern const std::string kApiVersion;

extern const int kMaxSocketReconnectCount;

extern const int kMaxPayloadLength;

extern const int kDefaultConnectivityCheckIntervalSec;

extern const int kSocketOpenTimeoutSec;

extern const int kSocketCloseTimeoutSec;

extern const int kUpdateAuthTokenTimeoutSec;

extern const int kRequestTimeoutSec;

extern const int kResponseTimeoutSec;

extern const int kConnectivityCheckTimeoutSec;

extern const int kDisposeWaitTimeoutSec;

}  // namespace config
}  // namespace signaling
}  // namespace skyway

#endif
