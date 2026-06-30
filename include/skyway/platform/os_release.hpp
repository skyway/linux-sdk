//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLATFORM_OS_RELEASE_HPP_
#define SKYWAY_PLATFORM_OS_RELEASE_HPP_

#include <istream>
#include <string>

namespace skyway {
namespace platform {

std::string ParseOsInfoFromOsRelease(std::istream& input);
std::string ReadOsInfoFromOsRelease();

}  // namespace platform
}  // namespace skyway

#endif /* SKYWAY_PLATFORM_OS_RELEASE_HPP_ */
