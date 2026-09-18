//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_

#include <api/data_channel_interface.h>

#include <deque>
#include <mutex>

#include "skyway/core/interface/remote_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace remote {

class RemoteDataStream : public interface::RemoteStream {
public:
    using PublicationId = std::string;

    class Listener {
    public:
        virtual ~Listener() = default;

        virtual void OnData(const std::string& data)                  = 0;
        virtual void OnDataBuffer(const uint8_t* data, size_t length) = 0;
    };
    RemoteDataStream(const std::string& id);
    ~RemoteDataStream();
    void Dispose() override;

    void AddListener(Listener* listener);

    void RemoveListener(Listener* listener);

    void OnDataBuffer(const webrtc::DataBuffer& buffer);

    bool Enable() override;

    bool Disable() override;

private:
    struct BufferedData {
        enum class Type { kString, kBuffer };
        Type type;
        std::string data;
        std::vector<uint8_t> buffer;

        BufferedData(const std::string& str);
        BufferedData(const uint8_t* buf, size_t length);
    };

    void BufferData(BufferedData&& data);

    std::mutex listeners_mutex_;
    std::vector<Listener*> listeners_;
    std::atomic<bool> is_disposed_ = false;
    std::atomic<bool> is_enabled_  = true;

    std::mutex buffer_mutex_;
    std::deque<BufferedData> buffer_;
    size_t buffer_size_ = 0;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif
