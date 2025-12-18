//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_TOKEN_AUTH_TOKEN_HPP_
#define SKYWAY_TOKEN_AUTH_TOKEN_HPP_

#include <json.hpp>
#include <string>
#include <thread>
#include <vector>
#include <optional>

namespace skyway {
namespace token {

struct PublicationScope {
    std::vector<std::string> actions;
};

struct SubscriptionScope {
    std::vector<std::string> actions;
};

struct MemberScope {
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::vector<std::string> actions;
    std::optional<PublicationScope> publication;
    std::optional<SubscriptionScope> subscription;
};

struct ForwardingScope {
    std::vector<std::string> actions;
    std::optional<SubscriptionScope> subscription;
};

struct SfuBotScope {
    std::vector<std::string> actions;
    std::vector<ForwardingScope> forwardings;
};

struct ChannelScope {
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::vector<std::string> actions;
    std::vector<MemberScope> members;
    std::vector<SfuBotScope> sfu_bots;
};

struct AppScope {
    std::string id;
    bool turn;
    std::optional<bool> analytics;
    std::vector<std::string> actions;
    std::vector<ChannelScope> channels;
};

struct AuthTokenScopeV2 {
    AppScope app;
};

struct AuthToken {
    virtual ~AuthToken() = default;
    static std::unique_ptr<AuthToken> Create(const std::string& token);

    virtual std::string AppId() const = 0;
    std::string Jwt() const;
    virtual bool IsAnalyticsEnabled() const = 0;

    std::string jti;
    time_t iat;
    time_t exp;
    std::string jwt;
};

struct AuthTokenV2 : AuthToken {
    std::string AppId() const override;
    bool IsAnalyticsEnabled() const override;

    AuthTokenScopeV2 scope;
};

// for SAT v3
struct TurnScope {
    std::optional<bool> enabled;
};

struct AnalyticsScope {
    std::optional<bool> enabled;
};

struct SfuScope {
    std::optional<bool> enabled;
    std::optional<int> max_subscribers_limit;
};

struct MemberScopeV3 {
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::vector<std::string> methods;
};

struct RoomScope {
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::vector<std::string> methods;
    std::optional<MemberScopeV3> member;
    std::optional<SfuScope> sfu;
};

struct AuthTokenScopeV3 {
    std::string app_id;
    std::optional<TurnScope> turn;
    std::optional<AnalyticsScope> analytics;
    std::vector<RoomScope> rooms;
};

struct AuthTokenV3 : AuthToken {
    std::string AppId() const override;
    bool IsAnalyticsEnabled() const override;

    AuthTokenScopeV3 scope;
};

void from_json(const nlohmann::json& j, PublicationScope& scope);
void from_json(const nlohmann::json& j, SubscriptionScope& scope);
void from_json(const nlohmann::json& j, MemberScope& scope);
void from_json(const nlohmann::json& j, ForwardingScope& scope);
void from_json(const nlohmann::json& j, SfuBotScope& scope);
void from_json(const nlohmann::json& j, ChannelScope& scope);
void from_json(const nlohmann::json& j, AppScope& scope);
void from_json(const nlohmann::json& j, AuthTokenScopeV2& scope);
void from_json(const nlohmann::json& j, AuthToken& message);

// for SAT v3
void from_json(const nlohmann::json& j, TurnScope& scope);
void from_json(const nlohmann::json& j, AnalyticsScope& scope);
void from_json(const nlohmann::json& j, SfuScope& scope);
void from_json(const nlohmann::json& j, MemberScopeV3& scope);
void from_json(const nlohmann::json& j, RoomScope& scope);
void from_json(const nlohmann::json& j, AuthTokenScopeV3& scope);
void from_json(const nlohmann::json& j, AuthTokenV3& message);

}  // namespace token
}  // namespace skyway

#endif /* SKYWAY_TOKEN_AUTH_TOKEN_HPP_ */
