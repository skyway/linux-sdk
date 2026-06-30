//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_NETWORK_INTERFACE_WEBSOCKET_CLIENT_HPP_
#define SKYWAY_NETWORK_INTERFACE_WEBSOCKET_CLIENT_HPP_

#include <future>
#include <memory>
#include <unordered_map>
#include <vector>

namespace skyway {
namespace network {
namespace interface {

class WebSocketClient {
public:
    class Listener {
    public:
        virtual void OnMessage(const std::string& message) = 0;

        virtual void OnClose(const int code, const std::string& reason) {}

        virtual void OnError(const int code) {}
    };

    virtual ~WebSocketClient() = default;

    virtual void RegisterListener(Listener* listener) = 0;

    virtual std::future<bool> Connect(
        const std::string& url,
        const std::vector<std::string>& sub_protocols,
        const std::unordered_map<std::string, std::string>& headers) = 0;

    virtual std::future<bool> Send(const std::string& message) = 0;

    virtual std::future<bool> Close(const int code, const std::string& reason) = 0;

    std::future<bool> Close(const int code);

    std::future<bool> Close();

    virtual std::future<bool> Destroy() = 0;
};

class WebSocketClientFactory {
public:
    virtual ~WebSocketClientFactory()                 = default;
    virtual std::shared_ptr<WebSocketClient> Create() = 0;

    static void SetSharedInstance(std::unique_ptr<WebSocketClientFactory> factory);

    static WebSocketClientFactory* Shared();

private:
    static std::unique_ptr<WebSocketClientFactory> shared_;
};

}  // namespace interface
}  // namespace network
}  // namespace skyway

#endif
