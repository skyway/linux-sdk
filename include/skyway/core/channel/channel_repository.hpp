//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CHANNEL_CHANNEL_REPOSITORY_HPP_
#define SKYWAY_CORE_CHANNEL_CHANNEL_REPOSITORY_HPP_

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <unordered_set>

#include "skyway/core/channel/channel.hpp"
#include "skyway/core/interface/channel_repository.hpp"
#include "skyway/rtc_api/interface/client.hpp"

namespace skyway {
namespace core {
namespace channel {

class ChannelRepository : public interface::ChannelRepository {
public:
    ChannelRepository(std::weak_ptr<rtc_api::interface::Client> rtc_api);
    ~ChannelRepository();

    std::shared_ptr<Channel> Create(const model::Channel::Init& init) override;
    std::shared_ptr<Channel> Find(const model::Channel::Query& query) override;
    std::shared_ptr<Channel> FindOrCreate(const model::Channel::Init& init) override;
    void DisposeAllChannels() override;
    void Dispose() override;
    void ReleaseChannel(Channel* channel) override;

private:
    template <auto BuildChannelStateFunc, typename Arg>
    std::shared_ptr<Channel> BuildAndRegisterChannel(const Arg& arg, bool should_verify_opened);

    std::weak_ptr<rtc_api::interface::Client> rtc_api_;

    std::shared_mutex creation_mtx_;

    bool is_disposed_ = false;
    std::mutex channels_mtx_;
    std::unordered_set<std::shared_ptr<Channel>> channels_;
};

}  // namespace channel
}  // namespace core
}  // namespace skyway

#endif
