//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_GLOBAL_INTERFACE_LOGGER_HPP_
#define SKYWAY_GLOBAL_INTERFACE_LOGGER_HPP_

#include <boost/format.hpp>
#include <memory>
#include <mutex>

#include "skyway/global/interface/logger_observer.hpp"

#define __SKW_FILE__ skyway::global::interface::Logger::GetFileName(__FILE__)

#define SKW_TRACE(msg, ...)                                              \
    if (auto logger = skyway::global::interface::Logger::Shared()) {     \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);      \
        logger->Notify(skyway::global::interface::Logger::Level::kTrace, \
                       formatted,                                        \
                       __SKW_FILE__,                                     \
                       __FUNCTION__,                                     \
                       __LINE__);                                        \
        logger->Trace(formatted, __SKW_FILE__, __FUNCTION__, __LINE__);  \
    }

#define SKW_DEBUG(msg, ...)                                              \
    if (auto logger = skyway::global::interface::Logger::Shared()) {     \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);      \
        logger->Notify(skyway::global::interface::Logger::Level::kDebug, \
                       formatted,                                        \
                       __SKW_FILE__,                                     \
                       __FUNCTION__,                                     \
                       __LINE__);                                        \
        logger->Debug(formatted, __SKW_FILE__, __FUNCTION__, __LINE__);  \
    }

#define SKW_INFO(msg, ...)                                              \
    if (auto logger = skyway::global::interface::Logger::Shared()) {    \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);     \
        logger->Notify(skyway::global::interface::Logger::Level::kInfo, \
                       formatted,                                       \
                       __SKW_FILE__,                                    \
                       __FUNCTION__,                                    \
                       __LINE__);                                       \
        logger->Info(formatted, __SKW_FILE__, __FUNCTION__, __LINE__);  \
    }

#define SKW_WARN(msg, ...)                                              \
    if (auto logger = skyway::global::interface::Logger::Shared()) {    \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);     \
        logger->Notify(skyway::global::interface::Logger::Level::kWarn, \
                       formatted,                                       \
                       __SKW_FILE__,                                    \
                       __FUNCTION__,                                    \
                       __LINE__);                                       \
        logger->Warn(formatted, __SKW_FILE__, __FUNCTION__, __LINE__);  \
    }

#define SKW_ERROR(msg, ...)                                              \
    if (auto logger = skyway::global::interface::Logger::Shared()) {     \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);      \
        logger->Notify(skyway::global::interface::Logger::Level::kError, \
                       formatted,                                        \
                       __SKW_FILE__,                                     \
                       __FUNCTION__,                                     \
                       __LINE__);                                        \
        logger->Error(formatted, __SKW_FILE__, __FUNCTION__, __LINE__);  \
    }

#define SKW_TRACE_LOCAL(msg, ...)                                       \
    if (auto logger = skyway::global::interface::Logger::Shared()) {    \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);     \
        logger->Trace(formatted, __SKW_FILE__, __FUNCTION__, __LINE__); \
    }

#define SKW_DEBUG_LOCAL(msg, ...)                                       \
    if (auto logger = skyway::global::interface::Logger::Shared()) {    \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);     \
        logger->Debug(formatted, __SKW_FILE__, __FUNCTION__, __LINE__); \
    }

#define SKW_INFO_LOCAL(msg, ...)                                       \
    if (auto logger = skyway::global::interface::Logger::Shared()) {   \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);    \
        logger->Info(formatted, __SKW_FILE__, __FUNCTION__, __LINE__); \
    }

#define SKW_WARN_LOCAL(msg, ...)                                       \
    if (auto logger = skyway::global::interface::Logger::Shared()) {   \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);    \
        logger->Warn(formatted, __SKW_FILE__, __FUNCTION__, __LINE__); \
    }

#define SKW_ERROR_LOCAL(msg, ...)                                       \
    if (auto logger = skyway::global::interface::Logger::Shared()) {    \
        std::string formatted = logger->Format(msg, ##__VA_ARGS__);     \
        logger->Error(formatted, __SKW_FILE__, __FUNCTION__, __LINE__); \
    }

namespace skyway {
namespace global {
namespace interface {

class Logger {
public:
    enum Level { kOff, kTrace, kDebug, kInfo, kWarn, kError };

    static constexpr const char* kLogLevelTraceStr = "trace";
    static constexpr const char* kLogLevelDebugStr = "debug";
    static constexpr const char* kLogLevelInfoStr  = "info";
    static constexpr const char* kLogLevelWarnStr  = "warn";
    static constexpr const char* kLogLevelErrorStr = "error";

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

    void AddObserver(std::weak_ptr<LoggerObserver> observer);

    void Notify(Level log_level,
                const std::string& message,
                const std::string& filename,
                const std::string& function,
                int line);

    void BuildFormat() {}

    template <class Head, class... Tail>
    void BuildFormat(Head&& head, Tail&&... tail) {
        fmt_ = fmt_ % head;
        this->BuildFormat(std::forward<Tail>(tail)...);
    }

    template <class FormatString, class... Args>
    std::string Format(FormatString fmt_str, Args&&... args) {
        {
            std::lock_guard<std::mutex> lg(fmt_mtx_);
            fmt_ = boost::format(fmt_str);
            this->BuildFormat(args...);
            return fmt_.str();
        }
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

    static void SetSharedInstance(std::unique_ptr<Logger> logger);
    static std::shared_ptr<Logger> Shared();

private:
    static std::shared_ptr<Logger> shared_;
    std::weak_ptr<LoggerObserver> observer_;

    std::vector<LoggerObserver::SdkLog> sdk_log_buffer_;
    std::mutex sdk_log_buffer_mtx_;

    std::mutex fmt_mtx_;
    boost::format fmt_;
};

}  // namespace interface
}  // namespace global
}  // namespace skyway

#endif
