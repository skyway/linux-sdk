//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_DATA_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_DATA_STREAM_HPP_

#include <skyway/core/stream/local/data_stream.hpp>

#include "skyway/media/stream/interface/local/local_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace local {

class LocalDataStream : public LocalStream {
public:
    virtual ~LocalDataStream() = default;

    /// @brief 文字列を送信します。
    virtual bool Write(const std::string& data) const = 0;

    /// @brief バイト列を送信します。
    virtual bool Write(const uint8_t* data, size_t length) const = 0;
};

}  // namespace local
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_DATA_STREAM_HPP_
