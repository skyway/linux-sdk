//
//  error.hpp
//  skyway
//
//  Created by sandabu on 2022/07/25.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_GLOBAL_ERROR_HPP_
#define SKYWAY_GLOBAL_ERROR_HPP_

#include <string>

namespace skyway {
namespace global {

/// @brief SkyWayで発生したエラーを示す構造体
struct Error {
    // TODO: Impl code or type?
    std::string message;
};

}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_ERROR_HPP_ */
