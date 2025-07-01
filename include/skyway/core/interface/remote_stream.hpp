//
//  remote_stream.hpp
//  skyway
//
//  Created by sandabu on 2022/01/28.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_REMOTE_STREAM_HPP_
#define SKYWAY_CORE_INTERFACE_REMOTE_STREAM_HPP_

#include "skyway/core/interface/stream.hpp"

namespace skyway {
namespace core {
namespace interface {

/// @brief RemoteMemberで扱うStream
class RemoteStream : public Stream {
protected:
    RemoteStream(const std::string& id, model::ContentType content_type);
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_REMOTE_STREAM_HPP_ */
