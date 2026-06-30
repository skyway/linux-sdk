//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_ANALYTICS_CLIENT_FACTORY_HPP_
#define SKYWAY_CORE_ANALYTICS_CLIENT_FACTORY_HPP_

#include <memory>
#include <string>

#include "skyway/analytics/interface/analytics_client.hpp"

namespace skyway {

namespace core {

class AnalyticsClientFactory {
public:
    static std::shared_ptr<analytics::interface::AnalyticsClient> Create(
        const std::string& context_id);
};

}  // namespace core
}  // namespace skyway

#endif
