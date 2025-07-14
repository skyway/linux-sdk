//
//  capturer_video_source.hpp
//  skyway
//
//  Created by ogura on 2025/1/10.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_INTERFACE_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_INTERFACE_CAPTURER_VIDEO_SOURCE_HPP_

#include <media/base/adapted_video_track_source.h>

namespace skyway {
namespace media {
namespace interface {

class InternalCapturerVideoSource : public rtc::AdaptedVideoTrackSource {
public:
    virtual ~InternalCapturerVideoSource() = default;
};

class CapturerVideoSource {
public:
    virtual ~CapturerVideoSource() = default;

    virtual rtc::scoped_refptr<InternalCapturerVideoSource> GetSource() = 0;
};

}  // namespace interface
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_INTERFACE_CAPTURER_VIDEO_SOURCE_HPP_ */
