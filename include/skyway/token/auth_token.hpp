//
//  auth_token.hpp
//  skyway
//
//  Created by sandabu on 2022/01/12.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_TOKEN_AUTH_TOKEN_HPP_
#define SKYWAY_TOKEN_AUTH_TOKEN_HPP_

#include <boost/optional.hpp>
#include <json.hpp>
#include <string>
#include <thread>
#include <vector>

namespace skyway {
namespace token {

struct PublicationScope {
    std::vector<std::string> actions;
};

struct SubscriptionScope {
    std::vector<std::string> actions;
};

struct MemberScope {
    boost::optional<std::string> id;
    boost::optional<std::string> name;
    std::vector<std::string> actions;
    boost::optional<PublicationScope> publication;
    boost::optional<SubscriptionScope> subscription;
};

struct ForwardingScope {
    std::vector<std::string> actions;
    boost::optional<SubscriptionScope> subscription;
};

struct SfuBotScope {
    std::vector<std::string> actions;
    std::vector<ForwardingScope> forwardings;
};

struct ChannelScope {
    boost::optional<std::string> id;
    boost::optional<std::string> name;
    std::vector<std::string> actions;
    std::vector<MemberScope> members;
    std::vector<SfuBotScope> sfu_bots;
};

struct AppScope {
    std::string id;
    bool turn;
    boost::optional<bool> analytics;
    std::vector<std::string> actions;
    std::vector<ChannelScope> channels;
};

struct AuthTokenScope {
    AppScope app;
};

struct AuthToken {
    static std::unique_ptr<AuthToken> Create(const std::string& token);

    std::string AppId() const;
    std::string Jwt() const;

    std::string jti;
    time_t iat;
    time_t exp;
    AuthTokenScope scope;
    std::string jwt;
};

void from_json(const nlohmann::json& j, PublicationScope& scope);
void from_json(const nlohmann::json& j, SubscriptionScope& scope);
void from_json(const nlohmann::json& j, MemberScope& scope);
void from_json(const nlohmann::json& j, ForwardingScope& scope);
void from_json(const nlohmann::json& j, SfuBotScope& scope);
void from_json(const nlohmann::json& j, ChannelScope& scope);
void from_json(const nlohmann::json& j, AppScope& scope);
void from_json(const nlohmann::json& j, AuthTokenScope& scope);
void from_json(const nlohmann::json& j, AuthToken& message);

}  // namespace token
}  // namespace skyway

#endif /* SKYWAY_TOKEN_AUTH_TOKEN_HPP_ */
