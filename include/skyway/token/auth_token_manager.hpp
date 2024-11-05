//
//  auth_token_manager.hpp
//  skyway
//
//  Created by sandabu on 2022/02/24.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_TOKEN_AUTH_TOKEN_MANAGER_HPP_
#define SKYWAY_TOKEN_AUTH_TOKEN_MANAGER_HPP_

#include <condition_variable>
#include <mutex>
#include <unordered_set>

#include "skyway/core/context_options.hpp"
#include "skyway/token/auth_token.hpp"
#include "skyway/token/interface/auth_token_manager.hpp"

namespace skyway {
namespace token {

class AuthTokenManager : public interface::AuthTokenManager {
public:
    /// コンストラクタ
    /// @param options オプション
    AuthTokenManager(const core::ContextOptions::Token& options);
    ~AuthTokenManager();

    bool UpdateToken(const std::string& token) override;
    std::string AppId() const override;
    std::string Jwt() const override;
    bool IsAnalyticsEnabled() const override;

    void AddInternalListener(InternalListener* listener) override;
    void RemoveInternalListener(InternalListener* listener) override;

private:
    void JoinTimerThreadsIfNeeded();
    bool SetupTimers();
    std::mutex update_token_mtx_;
    Listener* listener_;
    std::unordered_set<interface::AuthTokenManager::InternalListener*> internal_listeners_;
    boost::optional<int> remind_time_in_sec_;
    std::unique_ptr<AuthToken> auth_token_;
    bool timer_canceled_;
    std::condition_variable timer_cv_;
    std::mutex timer_mtx_;
    std::unique_ptr<std::thread> remind_timer_thread_;
    std::unique_ptr<std::thread> expire_timer_thread_;
};

}  // namespace token
}  // namespace skyway

#endif /* SKYWAY_TOKEN_AUTH_TOKEN_MANAGER_HPP_ */
