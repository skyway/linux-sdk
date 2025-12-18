//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_PLUGIN_UNKNOWN_PLUGIN_MEMBER_HPP_
#define SKYWAY_PLUGIN_UNKNOWN_PLUGIN_MEMBER_HPP_

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/remote_member.hpp"

namespace skyway {
namespace plugin {
namespace unknown_plugin {

/// @brief 機能として対応していないメンバー
class UnknownMember : public core::interface::RemoteMember {
public:
    UnknownMember(std::shared_ptr<core::interface::Channel> channel, const model::Member& dto);
};

}  // namespace unknown_plugin
}  // namespace plugin
}  // namespace skyway

#endif /* SKYWAY_PLUGIN_UNKNOWN_PLUGIN_MEMBER_HPP_ */
