//
//  context_options.hpp
//  skyway
//
//  Created by riad on 2023/05/08.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_OPTIONS_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_OPTIONS_HPP_

#include <boost/optional.hpp>

namespace skyway {
namespace plugin {
namespace sfu_options {

/// @brief SfuBotのオプション
struct SfuOptionsParams {
    /// @brief Sfuサーバーの接続先
    boost::optional<std::string> domain;
    /// @brief Sfuサーバーのバージョン
    boost::optional<int> version;
    /// @brief Sfuサーバーのセキュリティフラグ
    boost::optional<bool> secure;
};

}  // namespace sfu_options
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_OPTIONS_HPP_ */
