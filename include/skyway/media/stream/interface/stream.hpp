//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_STREAM_HPP_

#include <string>

#include "skyway/domain/domain.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {

class Stream {
public:
    virtual ~Stream() = default;

    /// @brief Idを取得します。
    virtual std::string Id() = 0;

    /// @brief Side(LocalかRemoteか)を取得します。
    virtual domain::Side Side() = 0;

    /// @brief ContentType(VideoかAudioかDataか)を取得します。
    virtual domain::ContentType ContentType() = 0;
};

}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_STREAM_HPP_
