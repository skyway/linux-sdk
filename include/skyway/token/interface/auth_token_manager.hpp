//
//  auth_token_manager_interface.hpp
//  skyway
//
//  Created by sandabu on 2022/06/15.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_TOKEN_INTERACE_AUTH_TOKEN_MANAGER_HPP_
#define SKYWAY_TOKEN_INTERACE_AUTH_TOKEN_MANAGER_HPP_

#include "skyway/token/auth_token.hpp"

namespace skyway {
namespace token {
namespace interface {

/// 認証JWT管理マネージャ
class AuthTokenManager {
public:
    class Listener {
    public:
        /// 設定したリマインド時間に応じてコールされるリマインダコールバック関数
        virtual void OnTokenRefreshingNeeded() {}
        /// トークンが失効した時にコールされるコールバック関数
        virtual void OnTokenExpired() {}
    };
    /// libskywayで利用する内部イベントリスナ
    class InternalListener {
    public:
        virtual void OnTokenUpdated(const AuthToken* token) = 0;
    };

    virtual ~AuthTokenManager() = default;

    /// @brief トークンを更新します。
    /// @details 最初の初期トークンもこのメソッドを利用します。
    /// @param token JWT
    virtual bool UpdateToken(const std::string& token) = 0;

    /// @brief アプリケーションIDを返します。
    virtual std::string AppId() const = 0;

    /// @brief JWTを返します
    virtual std::string Jwt() const = 0;

    /// @brief Analyticsが有効かどうかを返します。
    virtual bool IsAnalyticsEnabled() const = 0;

    virtual void AddInternalListener(InternalListener* listener)    = 0;
    virtual void RemoveInternalListener(InternalListener* listener) = 0;
};

}  // namespace interface
}  // namespace token
}  // namespace skyway

#endif /* SKYWAY_TOKEN_INTERACE_AUTH_TOKEN_MANAGER_HPP_ */
