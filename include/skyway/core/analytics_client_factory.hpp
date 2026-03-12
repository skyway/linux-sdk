//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
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
    static std::shared_ptr<analytics::interface::AnalyticsClient> Create(
        const std::string& context_id);
};

}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_ANALYTICS_CLIENT_FACTORY_HPP_ */
