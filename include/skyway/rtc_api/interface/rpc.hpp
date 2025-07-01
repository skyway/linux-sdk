//
//  rpc.hpp
//  skyway
//
//  Created by sandabu on 2022/06/21.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_RTC_API_INTERFACE_RPC_HPP_
#define SKYWAY_RTC_API_INTERFACE_RPC_HPP_

#include <json.hpp>

#include "skyway/rtc_api/rpc/dto/message.hpp"

namespace skyway {
namespace rtc_api {
namespace interface {

/// JSON-RPCモジュール
class Rpc {
public:
    using MessageId = std::string;
    /// イベントリスナ
    class Listener {
    public:
        virtual void OnNotified(const rpc::dto::RequestMessage& message) = 0;
        virtual void OnReconnected()                                     = 0;
    };

    virtual ~Rpc()                                                               = default;
    virtual bool Connect(const std::string& domain, bool secure)                 = 0;
    virtual std::optional<nlohmann::json> Request(const std::string& method,
                                                  const nlohmann::json& params,
                                                  const std::string& message_id) = 0;
    virtual void Close()                                                         = 0;
    // notify and batch are functions of standard JSON-RPC specification but we do not use them now.
    //    bool notify(const std::string& method, const nlohmann::json& params) const;
    virtual bool IsConnected() const                              = 0;
    virtual void AddPendingRequest(const std::string& method,
                                   const nlohmann::json& params,
                                   const std::string& message_id) = 0;
};

}  // namespace interface
}  // namespace rtc_api
}  // namespace skyway

#endif /* SKYWAY_RTC_API_INTERFACE_RPC_HPP_ */
