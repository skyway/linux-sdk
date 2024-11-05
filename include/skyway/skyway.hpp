//
//  skyway.hpp
//  skyway
//
//  Created by sandabu on 2021/05/20.
//  Copyright © 2021 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_SKYWAY_HPP_
#define SKYWAY_SKYWAY_HPP_

#include <boost/optional.hpp>
#include <string>

namespace skyway {

// General
static const unsigned VERSION_MAJOR = 2;
static const unsigned VERSION_MINOR = 1;
static const unsigned VERSION_PATCH = 3;

inline std::string GetVersionString() {
    // clang-format off
    return std::to_string(VERSION_MAJOR)
        + "." + std::to_string(VERSION_MINOR)
        + "." + std::to_string(VERSION_PATCH);
    // clang-format on
}

}  // namespace skyway

#endif /* SKYWAY_SKYWAY_HPP_ */
