//
//  ice_params_client.hpp
//  skyway
//
//  Created by sandabu on 2022/02/14.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_ICE_ICE_PARAMS_CLIENT_HPP_
#define SKYWAY_CORE_ICE_ICE_PARAMS_CLIENT_HPP_

#include <api/peer_connection_interface.h>

#include <boost/optional.hpp>

#include "skyway/core/context_options.hpp"
#include "skyway/core/ice/dto/response.hpp"
#include "skyway/core/interface/ice_params_client.hpp"
#include "skyway/network/interface/http_client.hpp"

namespace skyway {
namespace core {
namespace ice {

enum class Status {
    SUCCESS                = 200,
    INVALID_REQUEST_PARAMS = 400,
    INVALID_TOKEN          = 401,
    INTERNAL_SERVER_ERROR  = 500
};

/// IceParamsサーバのステートレスなクライアント
class IceParamsClient : public interface::IceParamsClient {
public:
    using HttpClientInterface = network::interface::HttpClient;
    /// コンストラクタ
    /// @param http HTTPクライアント
    IceParamsClient(HttpClientInterface* http, const ContextOptions::IceParams& options);

    /// @brief 利用可能なIceServer情報をサーバに問い合わせます。
    /// @details 認証トークンで許可されたMemberに対して情報を発行します。
    /// @param token 認証トークン
    /// @param member_id MemberID
    /// @param ttl 認証情報の有効期限(秒)
    /// @return Iceサーバの配列を返します。情報取得に失敗した場合は空配列を返します。
    webrtc::PeerConnectionInterface::IceServers FetchIceServers(
        const std::string& token,
        const std::string& channel_id,
        const std::string& member_id,
        boost::optional<int> ttl) const override;

private:
    HttpClientInterface* http_;
    ContextOptions::IceParams options_;
    std::string GetIceParamsEndoint() const;
    webrtc::PeerConnectionInterface::IceServers ConvertResponse(
        const dto::IceParamsResponse& response) const;
};

}  // namespace ice
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_ICE_ICE_PARAMS_CLIENT_HPP_ */
