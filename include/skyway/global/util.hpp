//
//  util.hpp
//  skyway
//
//  Created by sandabu on 2021/10/14.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_GLOBAL_UTIL_HPP_
#define SKYWAY_GLOBAL_UTIL_HPP_

#include <atomic>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <condition_variable>
#include <json.hpp>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "skyway/global/config.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace global {
namespace util {

/// @brief タイムアウト付きスピンロックを実行します。
/// @details 指定したタイムアウトミリ秒まで呼び出しスレッドをブロックします。
/// 解放条件を満たしたときtrueを返し、タイムアウトした場合はfalseを返します。
/// @param release_condition ブロックを抜けるための解放条件
/// @param timeout_ms タイムアウトミリ秒
inline bool SpinLockWithTimeoutMs(std::function<bool()> release_condition, int timeout_ms) {
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_ptr<std::thread> observer_thread = nullptr;
    bool is_succeeded                            = false;
    {
        std::unique_lock<std::mutex> lock(mtx);
        // The flag used for Spurious Wakeup
        bool is_notified                  = false;
        std::atomic<bool> result_returned = false;
        observer_thread                   = std::make_unique<std::thread>([&] {
            while (!release_condition()) {
                // Block this thread until release_condition will be true
                if (result_returned) {
                    return;
                }
            }
            std::lock_guard<std::mutex> lk(mtx);
            is_notified = true;
            cv.notify_one();
        });
        is_succeeded =
            cv.wait_for(lock, std::chrono::milliseconds(timeout_ms), [&] { return is_notified; });
        result_returned = true;
    }
    observer_thread->join();

    return is_succeeded;
}

inline bool SpinLockWithTimeoutMs(std::atomic<bool>& release_condition, int timeout_ms) {
    std::function<bool()> f = [&] { return release_condition.load(); };
    return SpinLockWithTimeoutMs(f, timeout_ms);
}

/// @brief タイムアウト付きスピンロックを実行します。
/// @details 指定したタイムアウト秒まで呼び出しスレッドをブロックします。
/// 解放条件を満たしたときtrueを返し、タイムアウトした場合はfalseを返します。
/// @param release_condition ブロックを抜けるための解放条件
/// @param timeout_sec タイムアウト秒
inline bool SpinLockWithTimeout(std::function<bool()> release_condition,
                                int timeout_sec = config::DEFAULT_TIMEOUT_SEC) {
    return SpinLockWithTimeoutMs(release_condition, timeout_sec * 1000);
}

inline bool SpinLockWithTimeout(std::atomic<bool>& release_condition,
                                int timeout_sec = config::DEFAULT_TIMEOUT_SEC) {
    return SpinLockWithTimeoutMs(release_condition, timeout_sec * 1000);
}

inline std::string Uuid() {
    auto id            = boost::uuids::random_generator()();
    std::string result = boost::lexical_cast<std::string>(id);
    return result;
}

// REF:
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

/// デリミタごとに文字列を分割し、ベクトルを生成します。
///
/// デリミタが存在しない場合、入力された文字のベクトル(要素1)を返します。
/// @param s 入力文字
/// @param delimiter 区切りデリミタ
inline std::vector<std::string> Split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token     = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

inline std::string DecodeBase64Token(const std::string& token) {
    using InputItr  = std::istreambuf_iterator<char>;
    using OutputItr = std::ostream_iterator<char>;
    using DecodeItr = boost::archive::iterators::
        transform_width<boost::archive::iterators::binary_from_base64<InputItr>, 8, 6, char>;

    std::stringstream input_stream, output_stream;
    input_stream << token;
    copy(DecodeItr(InputItr(input_stream)), DecodeItr(InputItr()), OutputItr(output_stream));
    std::string res;
    output_stream >> res;
    return res;
}

inline void SetEncodingIndexToIdIfNeeded(std::vector<model::Encoding>& encodings) {
    for (int i = 0; i < encodings.size(); i++) {
        if (!encodings[i].id) {
            encodings[i].id = std::to_string(i);
        }
    }
}

inline void SortEncodingsForMediaSoup(std::vector<model::Encoding>& encodings) {
    if (encodings.empty()) return;
    auto encoding = encodings[0];
    if (encoding.max_bitrate) {
        std::sort(encodings.begin(),
                  encodings.end(),
                  [](const model::Encoding& lhs, const model::Encoding& rhs) {
                      if (lhs.max_bitrate == boost::none || rhs.max_bitrate == boost::none) {
                          return true;
                      }
                      return *lhs.max_bitrate < *rhs.max_bitrate;
                  });
    } else if (encoding.scale_resolution_down_by) {
        std::sort(encodings.begin(),
                  encodings.end(),
                  [](const model::Encoding& lhs, const model::Encoding& rhs) {
                      if (lhs.scale_resolution_down_by == boost::none ||
                          rhs.scale_resolution_down_by == boost::none) {
                          return true;
                      }
                      return *lhs.scale_resolution_down_by > *rhs.scale_resolution_down_by;
                  });
    } else if (encoding.max_framerate) {
        std::sort(encodings.begin(),
                  encodings.end(),
                  [](const model::Encoding& lhs, const model::Encoding& rhs) {
                      if (lhs.max_framerate == boost::none || rhs.max_framerate == boost::none) {
                          return true;
                      }
                      return *lhs.max_framerate < *rhs.max_framerate;
                  });
    }
}

inline const std::chrono::milliseconds CurrentUnixTimestampMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
}

}  // namespace util
}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_UTIL_HPP_ */
