//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SIGNALING_SIGNALING_CLIENT_FACTORY_HPP_
#define SKYWAY_SIGNALING_SIGNALING_CLIENT_FACTORY_HPP_

#include "skyway/signaling/interface/signaling_client_factory.hpp"

namespace skyway {
namespace signaling {

class SignalingClientFactory : public interface::SignalingClientFactory {
public:
    std::unique_ptr<interface::SignalingClient> Create(
        const std::string& channel_id,
        const std::optional<std::string>& channel_name,
        const interface::Member& member) override;
};

}  // namespace signaling
}  // namespace skyway

#endif
