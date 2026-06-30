//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CONFIG_HPP_
#define SKYWAY_CORE_CONFIG_HPP_

#include <cstddef>
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

extern const int kDefaultKeepAliveIntervalGapSec;
extern const int kDefaultKeepAliveIntervalSec;
extern const int kInfiniteKeepAliveInterval;
}  // namespace member

namespace data_stream {

extern const size_t kRemoteDataStreamMaxBufferSize;
}

extern const std::string kLocalDataStreamLabel;

extern const std::string kRemoteDataStreamJsObjectFlag;

}  // namespace config
}  // namespace core
}  // namespace skyway

#endif
