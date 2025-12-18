//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_CHUNK_MESSENGER_CHUNK_MESSENGER_FACTORY_HPP_
#define SKYWAY_CORE_CHUNK_MESSENGER_CHUNK_MESSENGER_FACTORY_HPP_

#include "skyway/core/interface/chunk_messenger_factory.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace chunk_messenger {

class ChunkMessengerFactory : public interface::ChunkMessengerFactory {
public:
    std::unique_ptr<interface::ChunkMessenger> Create(std::shared_ptr<interface::Channel> channel,
                                                      const model::Member& member) override;
};

}  // namespace chunk_messenger
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CHUNK_MESSENGER_CHUNK_MESSENGER_FACTORY_HPP_ */
