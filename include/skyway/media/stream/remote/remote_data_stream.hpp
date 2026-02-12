//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_DATA_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_DATA_STREAM_HPP_

#include <skyway/core/stream/remote/data_stream.hpp>

namespace skyway {
namespace media {
namespace stream {
namespace remote {

class RemoteDataStream : public skyway::core::stream::remote::RemoteDataStream {
public:
    RemoteDataStream(std::shared_ptr<skyway::core::stream::remote::RemoteDataStream> core);

    // skyway::core::stream::remote::RemoteDataStream
    void AddListener(skyway::core::stream::remote::RemoteDataStream::Listener* listener) override;
    void RemoveListener(
        skyway::core::stream::remote::RemoteDataStream::Listener* listener) override;

private:
    std::shared_ptr<skyway::core::stream::remote::RemoteDataStream> core_;
};

}  // namespace remote
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_REMOTE_REMOTE_DATA_STREAM_HPP_
