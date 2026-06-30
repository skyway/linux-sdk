//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_DOMAIN_CORE_CONVERT_HELPER_HPP_
#define SKYWAY_DOMAIN_CORE_CONVERT_HELPER_HPP_

#include <skyway/model/domain.hpp>

#include "skyway/domain/domain.hpp"

namespace skyway {
namespace domain {
namespace core_convert_helper {

/// @cond INTERNAL_SECTION
Side ConvertToPlatformSide(model::Side side);
ContentType ConvertToPlatformContentType(model::ContentType type);
/// @endcond

}  // namespace core_convert_helper
}  // namespace domain
}  // namespace skyway

#endif /* SKYWAY_DOMAIN_CORE_CONVERT_HELPER_HPP_ */
