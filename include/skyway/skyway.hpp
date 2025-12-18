//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SKYWAY_HPP_
#define SKYWAY_SKYWAY_HPP_

#include <string>

namespace skyway {

// General
static const unsigned kVersionMajor = 8;
static const unsigned kVersionMinor = 0;
static const unsigned kVersionPatch = 0;

inline std::string GetVersionString() {
    // clang-format off
    return std::to_string(kVersionMajor)
        + "." + std::to_string(kVersionMinor)
        + "." + std::to_string(kVersionPatch);
    // clang-format on
}

}  // namespace skyway

#endif /* SKYWAY_SKYWAY_HPP_ */
