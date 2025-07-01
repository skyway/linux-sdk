//
//  logger.hpp
//  skyway
//
//  Created by sandabu on 2021/05/26.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_GLOBAL_INTERFACE_LOGGER_HPP_
#define SKYWAY_GLOBAL_INTERFACE_LOGGER_HPP_

#include <boost/format.hpp>
#include <memory>
#include <mutex>

#define __SKW_FILE__ skyway::global::interface::Logger::GetFileName(__FILE__)

#define SKW_TRACE(msg, ...)                                                          \
    if (skyway::global::interface::Logger::Shared()) {                               \
        std::string formatted =                                                      \
            skyway::global::interface::Logger::Shared()->Format(msg, ##__VA_ARGS__); \
        skyway::global::interface::Logger::Shared()->Trace(                          \
            formatted, __SKW_FILE__, __FUNCTION__, __LINE__);                        \
    }

#define SKW_DEBUG(msg, ...)                                                          \
    if (skyway::global::interface::Logger::Shared()) {                               \
        std::string formatted =                                                      \
            skyway::global::interface::Logger::Shared()->Format(msg, ##__VA_ARGS__); \
        skyway::global::interface::Logger::Shared()->Debug(                          \
            formatted, __SKW_FILE__, __FUNCTION__, __LINE__);                        \
    }

#define SKW_INFO(msg, ...)                                                           \
    if (skyway::global::interface::Logger::Shared()) {                               \
        std::string formatted =                                                      \
            skyway::global::interface::Logger::Shared()->Format(msg, ##__VA_ARGS__); \
        skyway::global::interface::Logger::Shared()->Info(                           \
            formatted, __SKW_FILE__, __FUNCTION__, __LINE__);                        \
    }

#define SKW_WARN(msg, ...)                                                           \
    if (skyway::global::interface::Logger::Shared()) {                               \
        std::string formatted =                                                      \
            skyway::global::interface::Logger::Shared()->Format(msg, ##__VA_ARGS__); \
        skyway::global::interface::Logger::Shared()->Warn(                           \
            formatted, __SKW_FILE__, __FUNCTION__, __LINE__);                        \
    }

#define SKW_ERROR(msg, ...)                                                          \
    if (skyway::global::interface::Logger::Shared()) {                               \
        std::string formatted =                                                      \
            skyway::global::interface::Logger::Shared()->Format(msg, ##__VA_ARGS__); \
        skyway::global::interface::Logger::Shared()->Error(                          \
            formatted, __SKW_FILE__, __FUNCTION__, __LINE__);                        \
    }

namespace skyway {
namespace global {
namespace interface {

/// @brief SkyWayのログを処理するクラス
class Logger {
public:
    /// @brief ログレベル
    enum Level { kOff, kTrace, kDebug, kInfo, kWarn, kError };
    /// @cond INTERNAL_SECTION
    virtual ~Logger()            = default;
    virtual void Trace(const std::string& msg,
                       const std::string& filename,
                       const std::string& function,
                       int line) = 0;
    virtual void Debug(const std::string& msg,
                       const std::string& filename,
                       const std::string& function,
                       int line) = 0;
    virtual void Info(const std::string& msg,
                      const std::string& filename,
                      const std::string& function,
                      int line)  = 0;
    virtual void Warn(const std::string& msg,
                      const std::string& filename,
                      const std::string& function,
                      int line)  = 0;
    virtual void Error(const std::string& msg,
                       const std::string& filename,
                       const std::string& function,
                       int line) = 0;

    void BuildFormat() {}

    template <class Head, class... Tail>
    void BuildFormat(Head&& head, Tail&&... tail) {
        fmt_ = fmt_ % head;
        this->BuildFormat(std::forward<Tail>(tail)...);
    }

    template <class FormatString, class... Args>
    std::string Format(FormatString fmt_str, Args&&... args) {
        std::lock_guard<std::mutex> lg(fmt_mtx_);
        fmt_ = boost::format(fmt_str);
        this->BuildFormat(args...);
        return fmt_.str();
    }

    static inline std::string GetFileName(const std::string& path) {
        size_t pos1;

        pos1 = path.rfind('\\');
        if (pos1 != std::string::npos) {
            return path.substr(pos1 + 1, path.size() - pos1 - 1);
        }

        pos1 = path.rfind('/');
        if (pos1 != std::string::npos) {
            return path.substr(pos1 + 1, path.size() - pos1 - 1);
        }

        return path;
    }

    // Set value when Context::Setup()
    static void SetSharedInstance(std::unique_ptr<Logger> logger);
    static Logger* Shared();
    /// @endcond

private:
    static std::unique_ptr<Logger> shared_;

    std::mutex fmt_mtx_;
    boost::format fmt_;
};

}  // namespace interface
}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_INTERFACE_LOGGER_HPP_ */
