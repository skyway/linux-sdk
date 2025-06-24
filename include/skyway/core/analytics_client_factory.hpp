//
//  analytics_client_factory.hpp
//  skyway
//
//  Created by Muranaka Kei on 2024/01/15.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_CORE_ANALYTICS_CLIENT_FACTORY_HPP_
#define SKYWAY_CORE_ANALYTICS_CLIENT_FACTORY_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/channel.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {

class AnalyticsClientFactory {
public:
    static std::unique_ptr<analytics::interface::AnalyticsClient> Create(
        const std::shared_ptr<interface::Channel> channel, const model::Member& member);
};

}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_ANALYTICS_CLIENT_FACTORY_HPP_ */
