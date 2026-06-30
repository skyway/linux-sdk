//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_DATA_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_DATA_STREAM_HPP_

#include <mutex>
#include <unordered_map>

#include <skyway/media/stream/interface/remote/remote_data_stream.hpp>

#include "skyway/media/stream/abstract/stream_base.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace remote {

class RemoteDataStream
    : public abstract::StreamBase<interface::remote::RemoteDataStream,
                                  skyway::core::interface::RemoteStream,
                                  skyway::core::stream::remote::RemoteDataStream> {
public:
    /// @cond INTERNAL_SECTION
    RemoteDataStream(std::shared_ptr<skyway::core::stream::remote::RemoteDataStream> core);
    /// @endcond
    ~RemoteDataStream() override;

    void AddListener(interface::remote::RemoteDataStream::Listener* listener) override;
    void RemoveListener(interface::remote::RemoteDataStream::Listener* listener) override;

private:
    class CoreEventListenerAdapter
        : public skyway::core::stream::remote::RemoteDataStream::Listener {
    public:
        explicit CoreEventListenerAdapter(interface::remote::RemoteDataStream::Listener* listener);
        void OnData(const std::string& data) override;
        void OnDataBuffer(const uint8_t* data, size_t length) override;

    private:
        interface::remote::RemoteDataStream::Listener* listener_;
    };

    std::mutex listener_adapters_mtx_;
    std::unordered_map<interface::remote::RemoteDataStream::Listener*,
                       std::shared_ptr<CoreEventListenerAdapter>>
        listener_adapters_;
};

}  // namespace remote
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_DATA_STREAM_HPP_
