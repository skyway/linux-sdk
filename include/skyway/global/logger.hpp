//
//  logger.hpp
//  skyway
//
//  Created by ossan20 on 2023/8/18.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//
#ifndef SKYWAY_GLOBAL_LOGGER_HPP
#define SKYWAY_GLOBAL_LOGGER_HPP

#include <mutex>

#include <rtc_base/logging.h>

#include <skyway/global/interface/logger.hpp>

namespace skyway {
namespace global {

/// @brief SkyWayのログを出力するクラス
class Logger : public interface::Logger, public rtc::LogSink {
public:
    /// @brief Logger のリスナー
    /// @details ログに関する処理を実装する場合はこのクラスを継承してください。
    /// @attention
    /// ListenerでファイルI/Oなどの重い処理を実装する場合は別スレッドで実行するようにしてください。
    class Listener {
    public:
        virtual ~Listener() = default;
        /// @brief SkyWayのログが出力されたときのイベント
        /// @details ログに関する処理はこのメソッドをオーバーライドして実装してください。
        /// @param level ログレベルを表すenum
        /// @param text ログの内容
        virtual void OnLog(Level level, const std::string& text) = 0;
    };

    /// @brief 内部向けコンストラクタ
    /// @details 通常、このコンストラクタを呼び出す必要はありません。
    Logger(Level level = kInfo, bool enable_webrtc_log = false);
    ~Logger();

    /// @brief ログを出力します。
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void Log(Level level,
             const std::string& message,
             const std::string& filename = "",
             const std::string& function = "",
             int line                    = -1);

    /// @brief Traceレベルのログを出力します。
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void Trace(const std::string& message,
               const std::string& filename = __builtin_FILE(),
               const std::string& function = __builtin_FUNCTION(),
               int line                    = __builtin_LINE()) override;
    /// @brief Debugレベルのログを出力します。
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void Debug(const std::string& message,
               const std::string& filename = __builtin_FILE(),
               const std::string& function = __builtin_FUNCTION(),
               int line                    = __builtin_LINE()) override;
    /// @brief Infoレベルのログを出力します。
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void Info(const std::string& message,
              const std::string& filename = __builtin_FILE(),
              const std::string& function = __builtin_FUNCTION(),
              int line                    = __builtin_LINE()) override;
    /// @brief Warnレベルのログを出力します。
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void Warn(const std::string& message,
              const std::string& filename = __builtin_FILE(),
              const std::string& function = __builtin_FUNCTION(),
              int line                    = __builtin_LINE()) override;
    /// @brief Errorレベルのログを出力します。
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void Error(const std::string& message,
               const std::string& filename = __builtin_FILE(),
               const std::string& function = __builtin_FUNCTION(),
               int line                    = __builtin_LINE()) override;

    /// @brief WebRTCのログが出力されたときのイベント
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void OnLogMessage(const std::string& message) override;

    /// @brief WebRTCのログが出力されたときのイベント
    /// @details 通常、このメソッドを直接呼び出す必要はありません。
    void OnLogMessage(const std::string& message, rtc::LoggingSeverity severity) override;

    /// @brief ロガーのリスナーを登録します。
    /// @details SkyWayのログを出力するときに登録されたリスナーのイベントが発火します。
    /// @param listener Listenerクラスのポインタ
    static void RegisterListener(const std::shared_ptr<Listener> listener);

    /// @brief 登録済みのロガーのリスナーを消去します。
    static void UnregisterListener();

private:
    void SetLogLevel(Level level);
    Level WebRTCSeverityToLogLevel(rtc::LoggingSeverity severity);
    bool enable_webrtc_log_ = false;
    Level level_            = kInfo;
    inline static std::mutex listener_mtx_;
    inline static std::shared_ptr<Listener> listener_ = nullptr;
};

}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_LOGGER_HPP */
