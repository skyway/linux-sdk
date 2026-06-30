//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_AUDIO_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_AUDIO_STREAM_HPP_

#include "skyway/core/interface/remote_media_stream.hpp"

namespace rtc {
class Thread;
}

namespace skyway {
namespace core {
namespace stream {
namespace remote {

class RemoteAudioStream : public interface::RemoteMediaStream {
public:
    RemoteAudioStream(const std::string& id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track)
        : RemoteAudioStream(id, track, nullptr) {}
    RemoteAudioStream(const std::string& id,
                      rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track,
                      rtc::Thread* signaling_thread);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> GetTrack() const override;
    ~RemoteAudioStream();

    bool Enable() override;

    bool Disable() override;

private:
    void Dispose();

    std::atomic<bool> is_disposed_ = false;
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track_;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif
