//
//  video_renderer.hpp
//  skyway
//
//  Created by ogura on 2025/1/10.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_INTERFACE_VIDEO_RENDERER_HPP_
#define SKYWAY_MEDIA_INTERFACE_VIDEO_RENDERER_HPP_

#include <api/media_stream_interface.h>

namespace skyway {
namespace media {
namespace interface {

class VideoRenderer : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
public:
    virtual ~VideoRenderer() = default;
};

}  // namespace interface
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_INTERFACE_CAPTURER_VIDEO_SOURCE_HPP_ */
