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
static const unsigned VERSION_MAJOR = 4;
static const unsigned VERSION_MINOR = 0;
static const unsigned VERSION_PATCH = 0;

inline std::string GetVersionString() {
    // clang-format off
    return std::to_string(VERSION_MAJOR)
        + "." + std::to_string(VERSION_MINOR)
        + "." + std::to_string(VERSION_PATCH);
    // clang-format on
}

}  // namespace skyway

#endif /* SKYWAY_SKYWAY_HPP_ */
