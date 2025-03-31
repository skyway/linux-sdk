//
//  data_stream.hpp
//  skyway
//
//  Created by sandabu on 2022/01/28.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_STREAM_LOCAL_DATA_STREAM_HPP_
#define SKYWAY_CORE_STREAM_LOCAL_DATA_STREAM_HPP_

#include <atomic>
#include <mutex>

#include "skyway/core/interface/local_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace local {

using LocalStream = interface::LocalStream;

/// @brief LocalPersonで扱うDataStream
class LocalDataStream : public LocalStream {
public:
    using PublicationId = std::string;
    /// @cond INTERNAL_SECTION
    struct SendingData {
        bool is_binary;
        std::vector<uint8_t> data;
    };
    class InternalListener {
    public:
        virtual bool OnWriteData(const SendingData& buffer,
                                 const PublicationId& publication_id) = 0;
    };
    /// @endcond
    LocalDataStream();
    /// @cond INTERNAL_SECTION
    void AddInternalListener(const std::string& remote_member_id,
                             const PublicationId& publication_id,
                             InternalListener* listener);
    void RemoveInternalListener(const std::string& remote_member_id,
                                const PublicationId& publication_id);
    /// @endcond
    /// @brief 文字列を送信します。
    bool Write(const std::string& data) const;
    /// @brief バイト列を送信します。
    bool Write(const uint8_t* data, size_t length) const;

    /// @cond INTERNAL_SECTION
    /// @brief Dataの送信を開始します。
    bool Enable() override;
    /// @brief Dataの送信を停止します。
    bool Disable() override;
    /// @endcond

private:
    std::unordered_map<std::string, std::unordered_map<PublicationId, InternalListener*>>
        listeners_;
    mutable std::mutex listener_mtx_;
    std::atomic<bool> is_enabled_;
};

}  // namespace local
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_STREAM_LOCAL_DATA_STREAM_HPP_ */
