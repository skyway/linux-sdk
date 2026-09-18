//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_CHANNEL_REPOSITORY_HPP_
#define SKYWAY_CORE_INTERFACE_CHANNEL_REPOSITORY_HPP_

#include <memory>

#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace channel {
class Channel;
}

namespace interface {

class ChannelRepository {
public:
    virtual ~ChannelRepository() = default;

    virtual std::shared_ptr<channel::Channel> Create(const model::Channel::Init& init) = 0;

    virtual std::shared_ptr<channel::Channel> Find(const model::Channel::Query& query) = 0;

    virtual std::shared_ptr<channel::Channel> FindOrCreate(const model::Channel::Init& init) = 0;

    virtual void DisposeAllChannels() = 0;

    virtual void Dispose() = 0;

    virtual void ReleaseChannel(channel::Channel* channel) = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
