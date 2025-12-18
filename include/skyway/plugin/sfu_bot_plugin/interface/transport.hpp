//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_HPP_

namespace skyway {
namespace plugin {
namespace sfu_bot {
namespace interface {

class Transport {
public:
    virtual std::string GetId() const                            = 0;
    virtual std::string GetConnectionState() const               = 0;
    virtual void RestartIce(const nlohmann::json& iceParameters) = 0;
};

}  // namespace interface
}  // namespace sfu_bot
}  // namespace plugin
}  // namespace skyway

#endif  // SKYWAY_PLUGIN_SFU_BOT_PLUGIN_INTERFACE_TRANSPORT_HPP_
