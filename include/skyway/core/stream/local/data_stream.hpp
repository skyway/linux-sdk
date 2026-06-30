//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_LOCAL_DATA_STREAM_HPP_
#define SKYWAY_CORE_STREAM_LOCAL_DATA_STREAM_HPP_

#include <atomic>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

#include "skyway/core/interface/local_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace local {

using LocalStream = interface::LocalStream;

struct DataStreamSubscriber {
    std::string id;
    std::optional<std::string> name;
};

class LocalDataStream : public LocalStream {
public:
    using PublicationId = std::string;
    class Listener {
    public:
        virtual ~Listener() = default;
        virtual void OnWritable(const DataStreamSubscriber& subscriber) {}
        virtual void OnUnwritable(const DataStreamSubscriber& subscriber) {}
    };

    struct SendingData {
        bool is_binary;
        std::vector<uint8_t> data;
    };
    class InternalListener {
    public:
        virtual bool OnWriteData(const SendingData& buffer,
                                 const PublicationId& publication_id) = 0;
    };

    LocalDataStream();
    ~LocalDataStream();
    void AddListener(std::shared_ptr<Listener> listener);
    void RemoveListener();

    void SetIsWritable(bool is_writable,
                       const DataStreamSubscriber& subscriber,
                       const std::string& publication_id);
    void AddInternalListener(const std::string& remote_member_id,
                             const PublicationId& publication_id,
                             InternalListener* listener);
    void RemoveInternalListener(const std::string& remote_member_id,
                                const PublicationId& publication_id);

    bool Write(const std::string& data) const;

    bool Write(const uint8_t* data, size_t length) const;

    bool Enable() override;

    bool Disable() override;

private:
    std::unordered_map<std::string, std::unordered_map<PublicationId, InternalListener*>>
        internal_listeners_;
    mutable std::mutex internal_listeners_mtx_;
    std::atomic<bool> is_enabled_ = true;
    std::shared_ptr<Listener> listener_;
    mutable std::mutex listener_mtx_;
    std::unordered_map<std::string, bool> is_writable_states_;
    mutable std::mutex is_writable_states_mtx_;
};

}  // namespace local
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif
