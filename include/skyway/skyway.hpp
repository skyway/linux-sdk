//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_SKYWAY_HPP_
#define SKYWAY_SKYWAY_HPP_

#include <string>

namespace skyway {

static const unsigned kVersionMajor = 11;
static const unsigned kVersionMinor = 0;
static const unsigned kVersionPatch = 1;

inline std::string GetVersionString() {
    return std::to_string(kVersionMajor) + "." + std::to_string(kVersionMinor) + "." +
           std::to_string(kVersionPatch);
}

}  // namespace skyway

#endif
