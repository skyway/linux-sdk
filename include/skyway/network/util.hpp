//
//  util.hpp
//  skyway
//
//  Created by sandabu on 2021/05/20.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.

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

/// 指定したリトライ回数目(1,2,3...)に応じて、Exponential backoff And
/// Jitterにてスレッドをブロックします。
/// ブロックの解放条件を指定することができ、条件を満たした場合はtrueを返し、指定時間経過した場合はfalseを返します。
/// @param current_retry 指定するリトライ回数目
/// @param release_condition ブロックを抜けるための解放条件
inline bool ExponentialBackoffWait(
    int current_retry, std::function<bool()> release_condition = [] { return false; }) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, 100);
    int random = distr(eng);
    SKW_DEBUG("Exponential backoff: Jitter: %dms", random);
    int timeout = std::pow(current_retry, 2) * 100 + random;
    SKW_DEBUG("Exponential backoff: Estimated sleep time: %dms", timeout);
    return global::util::SpinLockWithTimeoutMs(release_condition, timeout);
}

inline nlohmann::json CreateBearerAuthHeader(const std::string& token) {
    // clang-format off
    return nlohmann::json{
        { "Authorization", "Bearer " + token }
    };
    // clang-format on
}

}  // namespace util
}  // namespace network
}  // namespace skyway

#endif /* SKYWAY_NETWORK_UTIL_HPP_ */
