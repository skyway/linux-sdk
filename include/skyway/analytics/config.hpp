//
//  config.hpp
//  skyway
//
//  Created by Muranaka Kei on 2023/11/24.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ANALYTICS_CONFIG_HPP_
#define SKYWAY_ANALYTICS_CONFIG_HPP_

namespace skyway {
namespace analytics {
namespace config {

/// デフォルトドメイン
constexpr char DEFAULT_DOMAIN[] = "analytics-logging.skyway.ntt.com";
/// セキュアプロトコル(HTTPS, WS)を利用するかどうか
constexpr bool DEFAULT_USE_SECURE_PROTOCOL = true;
/// APIバージョン
constexpr char API_VERSION[] = "v1";
/// Websocketの最大再接続試行回数
constexpr int MAX_SOCKET_RECONNECT_COUNT = 8;
/// ソケットオープンまでのタイムアウト時間(ミリ秒)
constexpr int SOCKET_OPEN_TIMEOUT_MILLISEC = 10 * 1000;
/// ソケットクローズまでのタイムアウト時間(ミリ秒)
constexpr int SOCKET_CLOSE_TIMEOUT_MILLISEC = 10 * 1000;

}  // namespace config
}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_CONFIG_HPP_ */
