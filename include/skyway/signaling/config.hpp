//
//  config.hpp
//  config
//
//  Created by sandabu on 2021/09/07.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_CONFIG_HPP_
#define SKYWAY_SIGNALING_CONFIG_HPP_

#include <string>

namespace skyway {
namespace signaling {
namespace config {

/// デフォルトドメイン
extern const std::string kDefaultDomain;
/// セキュアプロトコル(HTTPS, WS)を利用するかどうか
extern const bool kDefaultUseSecureProtocol;
/// APIバージョン
extern const std::string kApiVersion;
/// Websocketの最大再接続試行回数
extern const int kMaxSocketReconnectCount;
/// メッセージの最大文字数
extern const int kMaxPayloadLength;
/// 接続チェック応答のデフォルトインターバル時間(秒)
extern const int kDefaultConnectivityCheckIntervalSec;
/// ソケットオープンまでのタイムアウト時間(秒)
extern const int kSocketOpenTimeoutSec;
/// ソケットクローズまでのタイムアウト時間(秒)
extern const int kSocketCloseTimeoutSec;
/// UpdateSkywayAuthTokenまでのタイムアウト時間(秒)
extern const int kUpdateAuthTokenTimeoutSec;
/// リクエスト送信のタイムアウト時間(秒)
extern const int kRequestTimeoutSec;
/// レスポンス送信のタイムアウト時間(秒)
extern const int kResponseTimeoutSec;
/// ConnectivityCheckのタイムアウト時間(秒)
extern const int kConnectivityCheckTimeoutSec;

}  // namespace config
}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_CONFIG_HPP_ */
