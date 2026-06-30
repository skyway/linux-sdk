//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_OPTIONS_HPP_
#define SKYWAY_PLUGIN_SFU_BOT_PLUGIN_SFU_OPTIONS_HPP_

namespace skyway {
namespace plugin {
namespace sfu_options {

struct SfuOptionsParams {
    std::optional<std::string> domain;

    std::optional<int> version;

    std::optional<bool> secure;
};

}  // namespace sfu_options
}  // namespace plugin
}  // namespace skyway

#endif
