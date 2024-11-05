//
//  stream_factory.hpp
//  skyway
//
//  Created by iorar on 2024/10/28.
//  Copyright © 2024 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_FACTORY_HPP_
#define SKYWAY_MEDIA_STREAM_FACTORY_HPP_

#include "skyway/media/device_manager.hpp"

#include <skyway/core/stream/local/audio_stream.hpp>
#include <skyway/core/stream/local/data_stream.hpp>
#include <skyway/core/stream/local/video_stream.hpp>

namespace skyway {
namespace media {

/// @brief Streamの作成を行うクラス
class StreamFactory {
public:
    /// @brief LocalDataStreamを生成します。
    static std::shared_ptr<core::stream::local::LocalDataStream> CreateDataStream();

    /// @brief LocalAudioStreamを生成します。
    static std::shared_ptr<core::stream::local::LocalAudioStream> CreateAudioStream();

    /// @brief LocalVideoStreamを生成します。
    /// @param device StreamのソースになるVideoDevice
    static std::shared_ptr<core::stream::local::LocalVideoStream> CreateVideoStream(
        const DeviceManager::VideoDevice& device);

private:
};
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_STREAM_FACTORY_HPP_ */
