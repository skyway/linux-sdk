//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_TOKEN_INTERFACE_AUTH_TOKEN_MANAGER_HPP_
#define SKYWAY_TOKEN_INTERFACE_AUTH_TOKEN_MANAGER_HPP_

#include <string>

#include "skyway/token/auth_token.hpp"

namespace skyway {
namespace token {

namespace interface {

class AuthTokenManager {
public:
    class Listener {
    public:
        virtual void OnTokenRefreshingNeeded() {}

        virtual void OnTokenExpired() {}
    };

    class InternalListener {
    public:
        virtual void OnTokenUpdated(const AuthToken* token) = 0;
    };

    virtual ~AuthTokenManager() = default;

    virtual bool UpdateToken(const std::string& token) = 0;

    virtual std::string AppId() const = 0;

    virtual std::string Jwt() const = 0;

    virtual bool IsAnalyticsEnabled() const = 0;

    virtual bool IsSfuEnabled() const = 0;

    virtual void AddInternalListener(InternalListener* listener)    = 0;
    virtual void RemoveInternalListener(InternalListener* listener) = 0;
};

}  // namespace interface
}  // namespace token
}  // namespace skyway

#endif
