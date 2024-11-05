//
//  config.hpp
//  skyway
//
//  Created by sandabu on 2022/02/14.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_CONFIG_HPP_
#define SKYWAY_CORE_CONFIG_HPP_

#include <string>

namespace skyway {
namespace core {
namespace config {

namespace ice {
extern const std::string DEFAULT_PARAMS_SERVER_DOMAIN;
extern const int DEFAULT_PARAMS_SERVER_VERSION;
extern const bool DEFAULT_USE_SECURE_PROTOCOL;
extern const int TTL;

}  // namespace ice

namespace channel {
extern const int LOCAL_PERSON_CREATION_TIMEOUT_SEC;
}

namespace member {
/// The extra sec for `UpdateMemberTtl`
extern const int DEFAULT_KEEP_ALIVE_INTERVAL_GAP_SEC;
extern const int DEFAULT_KEEP_ALIVE_INTERVAL_SEC;
extern const int INFINITE_KEEP_ALIVE_INTERVAL;
}  // namespace member

extern const std::string LOCAL_DATA_STREAM_LABEL;
/// JS-SDKにおいてobject型を送信される時に付与されるフラグ文字列
extern const std::string REMOTE_DATA_STREAM_JS_OBJECT_FLAG;

}  // namespace config
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CONFIG_HPP_ */
