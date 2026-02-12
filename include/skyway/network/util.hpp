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

/// 指定したリトライ回数目(1,2,3...)に応じて、Exponential backoff And
/// Jitterにてスレッドをブロックします。
/// ブロックの解放条件を指定することができ、条件を満たした場合はtrueを返し、指定時間経過した場合はfalseを返します。
/// @param current_retry 指定するリトライ回数目
/// @param release_condition ブロックを抜けるための解放条件
/// @param release_condition_check_interval_ms 解放条件をチェックする間隔（ミリ秒）
/// @return ブロックが解放条件を満たして抜けた場合はtrue、タイムアウトした場合はfalseを返します。
inline bool ExponentialBackoffWaitWithReleaseCondition(
    int current_retry, std::function<bool()> release_condition, global::util::SleepIntervalMs release_condition_check_interval) {
    int timeout = CulculateRetryTimeoutMs(current_retry);
    return global::util::WaitUntilWithTimeoutMs(release_condition, release_condition_check_interval, timeout);
}

inline void ExponentialBackoffWait(int current_retry) {
    int timeout = CulculateRetryTimeoutMs(current_retry);
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
}

inline nlohmann::json CreateBearerAuthHeader(const std::string& token) {
    // clang-format off
    return nlohmann::json{
        { "Authorization", "Bearer " + token }
    };
    // clang-format on
}

std::string FormatCloseLog(int code, const std::string& reason);

}  // namespace util
}  // namespace network
}  // namespace skyway

#endif /* SKYWAY_NETWORK_UTIL_HPP_ */
