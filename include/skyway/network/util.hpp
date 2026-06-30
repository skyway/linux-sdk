//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_NETWORK_UTIL_HPP_
#define SKYWAY_NETWORK_UTIL_HPP_

#include <json.hpp>
#include <random>
#include <string>
#include <thread>

#include "skyway/global/interface/logger.hpp"
#include "skyway/global/util.hpp"

namespace skyway {
namespace network {
namespace util {

inline int CulculateRetryTimeoutMs(int current_retry) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, 100);
    int random = distr(eng);
    SKW_DEBUG("Exponential backoff: Jitter: %dms", random);
    int timeout = std::pow(current_retry, 2) * 100 + random;
    SKW_DEBUG("Exponential backoff: Estimated sleep time: %dms", timeout);
    return timeout;
}

inline bool ExponentialBackoffWaitWithReleaseCondition(
    int current_retry,
    std::function<bool()> release_condition,
    global::util::SleepIntervalMs release_condition_check_interval) {
    int timeout = CulculateRetryTimeoutMs(current_retry);
    return global::util::WaitUntilWithTimeoutMs(
        release_condition, release_condition_check_interval, timeout);
}

inline void ExponentialBackoffWait(int current_retry) {
    int timeout = CulculateRetryTimeoutMs(current_retry);
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
}

inline nlohmann::json CreateBearerAuthHeader(const std::string& token) {
    return nlohmann::json{{"Authorization", "Bearer " + token}};
}

std::string FormatCloseLog(int code, const std::string& reason);

}  // namespace util
}  // namespace network
}  // namespace skyway

#endif
