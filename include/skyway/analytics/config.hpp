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

}  // namespace config
}  // namespace analytics
}  // namespace skyway

#endif /* SKYWAY_ANALYTICS_CONFIG_HPP_ */
