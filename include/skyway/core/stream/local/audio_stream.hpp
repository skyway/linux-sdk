//
//  audio_stream.hpp
//  skyway
//
//  Created by sandabu on 2022/01/12.
//  Copyright © 2022 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_CORE_STREAM_LOCAL_AUDIO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_LOCAL_AUDIO_STREAM_HPP_

#include "skyway/core/interface/local_media_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace local {

using LocalMediaStream = interface::LocalMediaStream;

/// @brief LocalPersonで扱うAudioStream
class LocalAudioStream : public LocalMediaStream {
public:
    LocalAudioStream(rtc::scoped_refptr<webrtc::AudioTrackInterface> track);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> Track() const override;

    /// @cond INTERNAL_SECTION
    /// @brief Audioの再生を開始します。
    bool Enable() override;
    /// @brief Audioの再生を停止します。
    bool Disable() override;
    /// @endcond

private:
    rtc::scoped_refptr<webrtc::AudioTrackInterface> track_;
};

}  // namespace local
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_STREAM_LOCAL_AUDIO_STREAM_HPP_ */
