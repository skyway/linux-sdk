//
//  config.hpp
//  config
//
//  Created by sandabu on 2021/09/07.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_SIGNALING_CONFIG_HPP_
#define SKYWAY_SIGNALING_CONFIG_HPP_

#include <string>

namespace skyway {
namespace signaling {
namespace config {

/// デフォルトドメイン
extern const std::string DEFAULT_DOMAIN;
/// セキュアプロトコル(HTTPS, WS)を利用するかどうか
extern const bool DEFAULT_USE_SECURE_PROTOCOL;
/// APIバージョン
extern const std::string API_VERSION;
/// Websocketの最大再接続試行回数
extern const int MAX_SOCKET_RECONNECT_COUNT;
/// メッセージの最大文字数
extern const int MAX_PAYLOAD_LENGTH;
/// 接続チェック応答のデフォルトインターバル時間(秒)
extern const int DEFAULT_CONNECTIVITY_CHECK_INTERVAL_SEC;
/// ソケットオープンまでのタイムアウト時間(秒)
extern const int SOCKET_OPEN_TIMEOUT_SEC;
/// ソケットクローズまでのタイムアウト時間(秒)
extern const int SOCKET_CLOSE_TIMEOUT_SEC;
/// UpdateSkywayAuthTokenまでのタイムアウト時間(秒)
extern const int UPDATE_AUTH_TOKEN_TIMEOUT_SEC;
/// リクエスト送信のタイムアウト時間(秒)
extern const int REQUEST_TIMEOUT_SEC;
/// レスポンス送信のタイムアウト時間(秒)
extern const int RESPONSE_TIMEOUT_SEC;
/// ConnectivityCheckのタイムアウト時間(秒)
extern const int CONNECTIVITY_CHECK_TIMEOUT_SEC;

}  // namespace config
}  // namespace signaling
}  // namespace skyway

#endif /* SKYWAY_SIGNALING_CONFIG_HPP_ */
