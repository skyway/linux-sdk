//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_DATA_STREAM_HPP_
#define SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_DATA_STREAM_HPP_

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

#include "skyway/media/stream/interface/local/local_stream.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace interface {
namespace local {

class LocalDataStream : public LocalStream {
public:
    /// @brief データの送信先となるSubscriberの情報
    struct Subscriber {
        /// @brief SubscriberのMemberId
        std::string id;
        /// @brief SubscriberのMember名
        std::optional<std::string> name;
    };

    /// @brief データ送信可否イベントリスナ
    class Listener {
    public:
        virtual ~Listener() = default;

        /// @brief Subscriberへデータを送信できるようになった際に呼び出されます。
        /// @param subscriber 送信できるようになったSubscriberの情報
        virtual void OnWritable(const Subscriber& subscriber) = 0;

        /// @brief Subscriberへデータを送信できなくなった際に呼び出されます。
        /// @param subscriber 送信できなくなったSubscriberの情報
        virtual void OnUnwritable(const Subscriber& subscriber) = 0;
    };

    virtual ~LocalDataStream() = default;

    /// @brief 文字列を送信します。
    virtual bool Write(const std::string& data) const = 0;

    /// @brief バイト列を送信します。
    virtual bool Write(const uint8_t* data, size_t length) const = 0;

    /// @brief LocalDataStream::Listenerを登録します。
    /// @details 既に登録済みのイベントリスナーがある場合は上書きされます。
    /// @param listener データ送信可否イベントが発生した際に呼ばれるイベントリスナー
    virtual void AddListener(Listener* listener) = 0;

    /// @brief イベントリスナーの登録を解除します。
    virtual void RemoveListener() = 0;
};

}  // namespace local
}  // namespace interface
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_INTERFACE_LOCAL_LOCAL_DATA_STREAM_HPP_
