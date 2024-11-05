//
//  config.hpp
//  skyway
//
//  Created by sandabu on 2021/11/08.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_RTC_API_CONFIG_HPP_
#define SKYWAY_RTC_API_CONFIG_HPP_

#include <string>

namespace skyway {
namespace rtc_api {
namespace config {

extern const std::string JSON_RPC_VERSION;
extern const std::string DEFAULT_RAPI_DOMAIN;
extern const bool DEFAULT_SECURE;
extern const int MAX_RETRY_CONNECT;
extern const int WAITING_TIME_FOR_CONNECT;
extern const int WAITING_TIME_FOR_PACKET;
extern const int MAX_RETRY_SEND;
extern const int DEFAULT_TIMEOUT_FOR_SEND;

}  // namespace config
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_CONFIG_HPP_ */
