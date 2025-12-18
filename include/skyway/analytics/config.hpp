//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ANALYTICS_CONFIG_HPP_
#define SKYWAY_ANALYTICS_CONFIG_HPP_

namespace skyway {
namespace analytics {
namespace config {

/// デフォルトドメイン
constexpr char kDefaultDomain[] = "analytics-logging.skyway.ntt.com";
/// セキュアプロトコル(HTTPS, WS)を利用するかどうか
constexpr bool kDefaultUseSecureProtocol = true;
/// APIバージョン
constexpr char kApiVersion[] = "v1";
/// Websocketの最大再接続試行回数
constexpr int kMaxSocketReconnectCount = 8;
/// ソケットオープンまでのタイムアウト時間(ミリ秒)
constexpr int kSocketOpenTimeoutMillisec = 10 * 1000;
/// ソケットクローズまでのタイムアウト時間(ミリ秒)
constexpr int kSocketCloseTimeoutMillisec = 10 * 1000;
/// ソケット送信再試行間隔(ミリ秒)
constexpr int kSocketResendIntervalMillisec = 30 * 1000;
constexpr int kMaxRetryCount = 6;
constexpr std::chrono::seconds kInitialBackoff{1};
constexpr std::chrono::seconds kMaxBackoff{16};

}  // namespace config
}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_CONFIG_HPP_ */
