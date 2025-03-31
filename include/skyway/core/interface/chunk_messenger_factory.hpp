//
//  chunk_messenger_factory.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/07/05.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_FACTORY_HPP_
#define SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_FACTORY_HPP_

#include "skyway/core/interface/channel.hpp"
#include "skyway/core/interface/chunk_messenger.hpp"
#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class ChunkMessengerFactory {
public:
    virtual ~ChunkMessengerFactory()                                            = default;
    virtual std::unique_ptr<ChunkMessenger> Create(std::shared_ptr<interface::Channel> channel,
                                                   const model::Member& member) = 0;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_CHUNK_MESSENGER_FACTORY_HPP_ */
