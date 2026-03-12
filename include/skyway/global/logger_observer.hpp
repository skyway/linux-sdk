//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_GLOBAL_REMOTE_LOGGER_HPP
#define SKYWAY_GLOBAL_REMOTE_LOGGER_HPP

#include <future>

#include "skyway/analytics/client_event.hpp"
#include "skyway/global/interface/logger.hpp"
#include "skyway/global/interface/logger_observer.hpp"

namespace skyway {
namespace global {

class LoggerObserver : public skyway::global::interface::LoggerObserver {
public:
    LoggerObserver();

    ~LoggerObserver() override;

    void StopSendingLogs();

    void OnLog(const std::string& log_level,
               const std::string& message,
               const std::string& filename,
               const std::string& function,
               int line) override;

    void OnLogs(std::vector<SdkLog> sdkLogs) override;

    virtual std::future<bool> SendSDKLogAsync(const analytics::SDKLogsPayload& payload) = 0;

private:
    static constexpr size_t kMaxBufferSize     = 50;
    static constexpr int kFlushIntervalSeconds = 5;
    std::string BuildLogMessage(const std::string& level,
                                const std::string& message,
                                const std::string& filename,
                                const std::string& function,
                                int line);

    void FlushLoop();
    void SendSdkLogs();

    std::vector<analytics::SDKLogsPayload::SDKLog> buffer_;
    std::mutex buffer_mtx_;
    std::condition_variable cv_;
    std::thread flush_thread_;
    std::atomic<bool> stop_thread_               = false;
    std::atomic<bool> is_sending_thread_stopped_ = false;
};
}  // namespace global
}  // namespace skyway

#endif  // SKYWAY_GLOBAL_REMOTE_LOGGER_HPP
