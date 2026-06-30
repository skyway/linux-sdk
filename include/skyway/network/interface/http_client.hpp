//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_HTTP_CLIENT_HPP_
#define SKYWAY_NETWORK_INTERFACE_HTTP_CLIENT_HPP_

#include <future>
#include <json.hpp>
#include <optional>
namespace skyway {
namespace network {
namespace interface {

class HttpClient {
public:
    struct Response {
        int status;
        nlohmann::json body;
        nlohmann::json header;
    };
    virtual ~HttpClient() = default;

    virtual std::future<std::optional<Response>> Request(const std::string& url,
                                                         const std::string& method,
                                                         const nlohmann::json& header,
                                                         const nlohmann::json& body) = 0;

    static void SetSharedInstance(std::unique_ptr<HttpClient> http);

    static HttpClient* Shared();

    static const std::string kMethodGet;
    static const std::string kMethodPost;
    static const std::string kMethodPut;
    static const std::string kMethodDelete;

private:
    static std::unique_ptr<HttpClient> shared_;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif
