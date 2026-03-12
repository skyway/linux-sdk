//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_GLOBAL_INTERFACE_LOGGER_OBSERVER_HPP
#define SKYWAY_GLOBAL_INTERFACE_LOGGER_OBSERVER_HPP

namespace skyway {
namespace global {
namespace interface {

class LoggerObserver {
public:
    struct SdkLog {
        std::string level;
        std::string message;
        std::string filename;
        std::string function;
        int line;
    };

    virtual ~LoggerObserver() = default;

    virtual void OnLog(const std::string& log_level,
                       const std::string& message,
                       const std::string& filename,
                       const std::string& function,
                       int line)                     = 0;
    virtual void OnLogs(std::vector<SdkLog> sdkLogs) = 0;
};

}  // namespace interface
}  // namespace global
}  // namespace skyway

#endif  // SKYWAY_GLOBAL_INTERFACE_LOGGER_OBSERVER_HPP
