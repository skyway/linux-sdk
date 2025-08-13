//
//  skyway.hpp
//  skyway
//
//  Created by sandabu on 2021/05/20.
//  Copyright © 2021 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_SKYWAY_HPP_
#define SKYWAY_SKYWAY_HPP_

#include <string>

namespace skyway {

// General
static const unsigned kVersionMajor = 6;
static const unsigned kVersionMinor = 1;
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
