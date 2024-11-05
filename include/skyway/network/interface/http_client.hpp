//
//  http_client.hpp
//  skyway
//
//  Created by sandabu on 2021/10/11.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_HTTP_CLIENT_HPP_
#define SKYWAY_NETWORK_INTERFACE_HTTP_CLIENT_HPP_

#include <boost/optional.hpp>
#include <future>
#include <json.hpp>

namespace skyway {
namespace network {
namespace interface {

/// @brief HTTPクライアント
///
/// @details Platformにてこのインターフェースを実装して、Context::Setupに渡してください。
class HttpClient {
public:
    struct Response {
        int status;
        nlohmann::json body;
        nlohmann::json header;
    };
    virtual ~HttpClient() = default;
    /// @brief HTTPリクエストを行い、レスポンスボディを取得します。
    /// @details エラー、またはレスポンスが不正の場合boost::noneを返します。
    /// @param url リクエストURL
    /// @param method HTTP リクエストメソッド(GET |  POST | PUT | DELETE)
    /// @param header HTTP リクエストヘッダ
    /// @param body HTTP リクエストボディ
    virtual std::future<boost::optional<Response>> Request(const std::string& url,
                                                           const std::string& method,
                                                           const nlohmann::json& header,
                                                           const nlohmann::json& body) = 0;
    /// @brief HTTPクライアントをセットします。
    /// @details `Context::Setup()`内でセットします。
    /// @param http HTTPクライアント
    static void SetSharedInstance(std::unique_ptr<HttpClient> http);

    /// HTTPクライアントポインタを取得します。
    static HttpClient* Shared();

    static const std::string METHOD_GET;
    static const std::string METHOD_POST;
    static const std::string METHOD_PUT;
    static const std::string METHOD_DELETE;

private:
    static std::unique_ptr<HttpClient> shared_;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif /* SKYWAY_NETWORK_INTERFACE_HTTP_CLIENT_HPP_ */
