//
//  i420_capturer_video_source.hpp
//  skyway
//
//  Created by ogura on 2025/1/10.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_INTERFACE_I420_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_INTERFACE_I420_CAPTURER_VIDEO_SOURCE_HPP_

#include <mutex>
#include <unordered_set>

#include "skyway/core/stream/remote/video_stream.hpp"
#include "skyway/media/interface/capturer_video_source.hpp"

namespace skyway {
namespace media {
namespace interface {

class I420CapturerVideoSource : public InternalCapturerVideoSource {
public:
    virtual bool Render(int width,
                        int height,
                        const uint8_t* y,
                        const uint8_t* u,
                        const uint8_t* v,
                        int stride_y,
                        int stride_u,
                        int stride_v) = 0;
};

}  // namespace interface
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_INTERFACE_I420_CAPTURER_VIDEO_SOURCE_HPP_ */
