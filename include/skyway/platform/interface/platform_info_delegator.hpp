//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLATFORM_INTERFACE_PLATFORM_INFO_DELEGATOR_HPP_
#define SKYWAY_PLATFORM_INTERFACE_PLATFORM_INFO_DELEGATOR_HPP_

#include <memory>
#include <string>

namespace skyway {
namespace platform {
namespace interface {

class PlatformInfoDelegator {
public:
    virtual ~PlatformInfoDelegator() = default;

    virtual std::string GetPlatform() const = 0;

    virtual std::string GetOsInfo() const = 0;

    virtual std::string GetModelName() const = 0;

    virtual std::string GetSdkVersion() const = 0;

    static void SetSharedInstance(std::unique_ptr<PlatformInfoDelegator> delegator);

    static const PlatformInfoDelegator* const Shared();

private:
    static std::unique_ptr<PlatformInfoDelegator> shared_;
};

}  // namespace interface
}  // namespace platform
}  // namespace skyway

#endif
