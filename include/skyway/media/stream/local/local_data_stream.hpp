//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_DATA_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_DATA_STREAM_HPP_

#include <mutex>

#include <skyway/core/stream/local/data_stream.hpp>

#include "skyway/media/stream/abstract/stream_base.hpp"
#include "skyway/media/stream/interface/local/local_data_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace local {

class LocalDataStream : public abstract::StreamBase<interface::local::LocalDataStream,
                                                    skyway::core::interface::LocalStream,
                                                    skyway::core::stream::local::LocalDataStream> {
public:
    /// @cond INTERNAL_SECTION
    LocalDataStream();
    LocalDataStream(std::shared_ptr<skyway::core::stream::local::LocalDataStream> core);
    /// @endcond
    ~LocalDataStream() override;

    bool Write(const std::string& data) const override;
    bool Write(const uint8_t* data, size_t length) const override;

    void AddListener(interface::local::LocalDataStream::Listener* listener) override;
    void RemoveListener() override;

private:
    class CoreEventListenerAdapter : public skyway::core::stream::local::LocalDataStream::Listener {
    public:
        explicit CoreEventListenerAdapter(interface::local::LocalDataStream::Listener* listener);
        void OnWritable(
            const skyway::core::stream::local::DataStreamSubscriber& subscriber) override;
        void OnUnwritable(
            const skyway::core::stream::local::DataStreamSubscriber& subscriber) override;

    private:
        interface::local::LocalDataStream::Listener* listener_;
    };

    std::mutex listener_adapter_mtx_;
    std::shared_ptr<CoreEventListenerAdapter> listener_adapter_;
};

}  // namespace local
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_LOCAL_LOCAL_DATA_STREAM_HPP_
