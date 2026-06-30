//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_DATA_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_DATA_STREAM_HPP_

#include <skyway/core/stream/remote/data_stream.hpp>

#include "skyway/media/stream/interface/remote/remote_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace remote {

class RemoteDataStream : public RemoteStream {
public:
    /// @brief データ受信イベントリスナ
    class Listener {
    public:
        virtual ~Listener() = default;

        /// @brief 文字列データを受信した際に呼び出されます。
        /// @param data 受信した文字列データ
        virtual void OnData(const std::string& data) = 0;

        /// @brief バイナリデータを受信した際に呼び出されます。
        /// @param data 受信したバイナリデータ
        /// @param length バイナリデータの長さ
        virtual void OnDataBuffer(const uint8_t* data, size_t length) = 0;
    };

    virtual ~RemoteDataStream() = default;

    /// @brief RemoteDataStream::Listenerを登録します。
    /// @param listener データ受信イベントが発生した際に呼ばれるイベントリスナー
    virtual void AddListener(Listener* listener) = 0;

    /// @brief イベントリスナーの登録を解除します。
    /// @param listener 登録解除するイベントリスナー
    virtual void RemoveListener(Listener* listener) = 0;
};

}  // namespace remote
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_REMOTE_REMOTE_DATA_STREAM_HPP_
