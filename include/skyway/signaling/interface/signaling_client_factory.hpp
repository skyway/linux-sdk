//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_FACTORY_HPP_
#define SKYWAY_SIGNALING_INTERFACE_SIGNALING_CLIENT_FACTORY_HPP_

#include <memory>
#include <optional>
#include <string>

#include "skyway/signaling/interface/member.hpp"
#include "skyway/signaling/interface/signaling_client.hpp"

namespace skyway {
namespace signaling {
namespace interface {

class SignalingClientFactory {
public:
    virtual ~SignalingClientFactory()                                     = default;
    virtual std::unique_ptr<SignalingClient> Create(const std::string& channel_id,
                                                    const std::optional<std::string>& channel_name,
                                                    const Member& member) = 0;
};

}  // namespace interface
}  // namespace signaling
}  // namespace skyway

#endif
