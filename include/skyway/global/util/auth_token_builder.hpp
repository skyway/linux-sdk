//
//  auth_token_builder.hpp
//  skyway
//
//  Created by Kenta Katsura on 2025/07/29.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_GLOBAL_UTIL_AUTH_TOKEN_BUILDER_HPP_
#define SKYWAY_GLOBAL_UTIL_AUTH_TOKEN_BUILDER_HPP_

#include <json.hpp>
#include <string>

namespace skyway {
namespace global {
namespace util {

/// @cond INTERNAL_SECTION
class AuthTokenBuilder {
public:
    const static std::string Create(const std::string app_id, const std::string secret_key);

private:
    const static std::string EncodeBase64Url(const std::string& token);
    const static std::string BuildSHA256(const std::string& key, const std::string& data);
};
/// @endcond

}  // namespace util
}  // namespace global
}  // namespace skyway
#endif  // SKYWAY_GLOBAL_UTIL_AUTH_TOKEN_BUILDER_HPP_
