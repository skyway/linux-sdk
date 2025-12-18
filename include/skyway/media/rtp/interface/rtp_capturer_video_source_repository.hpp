//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_RTP_INTERFACE_RTP_CAPTURER_VIDEO_SOURCE_REPOSITORY_HPP_
#define SKYWAY_MEDIA_RTP_INTERFACE_RTP_CAPTURER_VIDEO_SOURCE_REPOSITORY_HPP_

#include <memory>
#include <vector>

#include "skyway/media/rtp/interface/rtp_capturer_video_source.hpp"

namespace skyway {
namespace media {
namespace rtp {
namespace interface {

/// @cond INTERNAL_SECTION
class RtpCapturerVideoSourceRepository {
public:
    virtual ~RtpCapturerVideoSourceRepository() = default;

    virtual std::optional<uint16_t> Register(
        std::shared_ptr<RtpCapturerVideoSource> video_source)                     = 0;
    virtual bool Unregister(std::shared_ptr<RtpCapturerVideoSource> video_source) = 0;
    virtual std::shared_ptr<RtpCapturerVideoSource> Find(const int& frame_id)     = 0;
};
/// @endcond

}  // namespace interface
}  // namespace rtp
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_RTP_INTERFACE_RTP_CAPTURER_VIDEO_SOURCE_REPOSITORY_HPP_ */
