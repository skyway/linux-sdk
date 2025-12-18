//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_REMOTE_MEDIA_STREAM_HPP_
#define SKYWAY_CORE_INTERFACE_REMOTE_MEDIA_STREAM_HPP_

#include <api/media_stream_interface.h>

#include "skyway/core/interface/remote_stream.hpp"

namespace skyway {
namespace core {
namespace interface {

/// @brief RemoteMemberで扱うMediaStream
class RemoteMediaStream : public RemoteStream {
public:
    virtual ~RemoteMediaStream() = default;

    /// @brief Trackを取得します。
    virtual rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack() const = 0;

protected:
    RemoteMediaStream(const std::string& id, model::ContentType content_type);
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_REMOTE_MEDIA_STREAM_HPP_ */
