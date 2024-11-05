//
//  chunk_messenger_factory.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/07/05.
//  Copyright © 2023 NTT Communications. All rights reserved.
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
    std::unique_ptr<interface::ChunkMessenger> Create(interface::Channel* channel,
                                                      const model::Member& member) override;
};

}  // namespace chunk_messenger
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_CHUNK_MESSENGER_CHUNK_MESSENGER_FACTORY_HPP_ */
