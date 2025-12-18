//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
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
