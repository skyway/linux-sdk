//
//  data_stream.hpp
//  skyway
//
//  Created by sandabu on 2022/01/31.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_
#define SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_

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
    void AddListener(Listener* listener);

    /// @cond INTERNAL_SECTION
    void OnDataBuffer(const webrtc::DataBuffer& buffer);
    /// @brief Dataの受信を開始します。
    bool Enable() override;
    /// @brief Dataの受信を停止します。
    bool Disable() override;
    /// @endcond

private:
    std::vector<Listener*> listeners_;
    std::atomic<bool> is_enabled_;
};

}  // namespace remote
}  // namespace stream
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_STREAM_REMOTE_DATA_STREAM_HPP_ */
