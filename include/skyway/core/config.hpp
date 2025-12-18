//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CONFIG_HPP_
#define SKYWAY_CORE_CONFIG_HPP_

#include <string>

namespace skyway {
namespace core {
namespace config {

namespace ice {
extern const std::string kDefaultParamsServerDomain;
extern const int kDefaultParamsServerVersion;
extern const bool kDefaultUseSecureProtocol;
extern const int kTtl;

}  // namespace ice

namespace channel {
extern const int kLocalPersonCreationTimeoutSec;
}

namespace member {
/// The extra sec for `UpdateMemberTtl`
extern const int kDefaultKeepAliveIntervalGapSec;
extern const int kDefaultKeepAliveIntervalSec;
extern const int kInfiniteKeepAliveInterval;
}  // namespace member

extern const std::string kLocalDataStreamLabel;
/// JS-SDKにおいてobject型を送信される時に付与されるフラグ文字列
extern const std::string kRemoteDataStreamJsObjectFlag;

}  // namespace config
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CONFIG_HPP_ */
