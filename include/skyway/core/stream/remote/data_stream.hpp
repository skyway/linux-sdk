//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_

#include <mutex>

#include <api/data_channel_interface.h>

#include "skyway/core/interface/remote_stream.hpp"

namespace skyway {
namespace core {
namespace stream {
namespace remote {

using RemoteStream = interface::RemoteStream;

/// @brief RemoteMemberで扱うDataStream
class RemoteDataStream : public RemoteStream {
public:
    using PublicationId = std::string;
    /// @brief データ受信イベントリスナ
    class Listener {
    public:
        virtual void OnData(const std::string& data)                  = 0;
        virtual void OnDataBuffer(const uint8_t* data, size_t length) = 0;
    };
    RemoteDataStream(const std::string& id);
    /// @brief データ受信イベントリスナを購読します。
    /// @param listener データ受信イベントリスナ
    virtual void AddListener(Listener* listener);
    
    /// @brief データ受信イベントリスナの購読を中止します。
    /// @param listener データ受信イベントリスナ
    virtual void RemoveListener(Listener* listener);

    /// @cond INTERNAL_SECTION
    void OnDataBuffer(const webrtc::DataBuffer& buffer);
    /// @brief Dataの受信を開始します。
    bool Enable() override;
    /// @brief Dataの受信を停止します。
    bool Disable() override;
    /// @endcond

private:
    std::mutex listeners_mutex_;
    std::vector<Listener*> listeners_;
    std::atomic<bool> is_enabled_;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_ */
