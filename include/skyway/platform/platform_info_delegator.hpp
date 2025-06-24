//
//  platform_info_delegator.hpp
//  skyway
//
//  Created by iorar on 2024/05/08.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_PLATFORM_PLATFORM_INFO_DELEGATOR_HPP_
#define SKYWAY_PLATFORM_PLATFORM_INFO_DELEGATOR_HPP_

#include "skyway/platform/interface/platform_info_delegator.hpp"

namespace skyway {
namespace platform {

class PlatformInfoDelegator : public interface::PlatformInfoDelegator {
public:
    std::string GetPlatform() const override;
    std::string GetOsInfo() const override;
    std::string GetModelName() const override;
    std::string GetSdkVersion() const override;

private:
    std::string RemoveString(std::string origin_str, std::string remove_str) const;
};

}  // namespace platform
}  // namespace skyway

#endif /* SKYWAY_PLATFORM_PLATFORM_INFO_DELEGATOR_HPP_ */
