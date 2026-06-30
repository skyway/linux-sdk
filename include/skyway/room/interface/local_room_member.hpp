//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_LOCAL_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_INTERFACE_LOCAL_ROOM_MEMBER_HPP

#include <skyway/core/interface/local_person.hpp>

#include "skyway/media/stream/interface/local/local_stream.hpp"

#include "skyway/room/interface/room_member.hpp"

namespace skyway {
namespace room {
namespace interface {

class RoomPublication;
class RoomSubscription;

/// @brief LocalRoomMemberの操作を行うインターフェース
class LocalRoomMember : public virtual RoomMember {
public:
    /// イベントリスナ
    class EventListener : public RoomMember::EventListener {
    public:
        virtual ~EventListener() = default;
        /// @brief このLocalRoomMemerがStreamをPublishした後に発生するイベント
        /// @param publication Publication
        virtual void OnStreamPublished(std::shared_ptr<RoomPublication> publication) {}

        /// @brief このLocalRoomMemerがUnpublishした後に発生するイベント
        /// @param publication Publication
        virtual void OnStreamUnpublished(std::shared_ptr<RoomPublication> publication) {}

        /// @brief このLocalRoomMemerがSubscribeした後に発生するイベント
        /// @param subscription Subscription
        virtual void OnPublicationSubscribed(std::shared_ptr<RoomSubscription> subscription) {}

        /// @brief このLocalRoomMemerがUnsubscribeした後に発生するイベント
        /// @param subscription Subscription
        virtual void OnPublicationUnsubscribed(std::shared_ptr<RoomSubscription> subscription) {}
    };

    /// @brief `Publish`時の設定
    struct PublicationOptions {
        /// @brief Metadata
        std::optional<std::string> metadata;
        /// @brief コーデック一覧
        std::vector<Codec> codec_capabilities;
        /// @brief エンコーディング一覧
        std::vector<Encoding> encodings;
        /// @brief `Publish`時の公開状態
        bool is_enabled = true;
        /// @brief `Subscriber`の最大人数
        /// @details この設定はtypeがkSFUのPublicationもしくはSFURoomでのみ有効です。
        /// 最大値は99です。
        int max_subscribers = 10;
        /// @brief PublicationのType
        /// @details 通信タイプ。この設定はRoomでのみ有効であり、P2PRoom/SFURoomでは無視されます。
        domain::PublicationType type = domain::PublicationType::kP2P;
    };

    /// @brief `Subscribe`時の設定
    struct SubscriptionOptions {
        /// @brief `Subscribe`時に選択するエンコーディング設定。
        /// @details `RoomPublication.Options.encodings`から選択する項目のIdを設定してください。
        std::optional<std::string> preferred_encoding_id;
    };

    virtual ~LocalRoomMember() = default;
    /// @brief イベントの購読します。
    virtual void AddEventListener(EventListener* listener) = 0;
    /// @brief イベントの購読を中止します。
    virtual void RemoveEventListener(EventListener* listener) = 0;
    /// @brief LocalStreamを公開します。
    virtual std::shared_ptr<RoomPublication> Publish(
        std::shared_ptr<media::stream::interface::local::LocalStream> stream,
        PublicationOptions options) = 0;
    /// @brief 公開されているPublicationを購読します。
    virtual std::shared_ptr<RoomSubscription> Subscribe(const std::string& publication_id,
                                                        SubscriptionOptions options) = 0;
    /// @brief 公開しているPublicationを非公開にします。
    virtual bool Unpublish(const std::string& publication_id) = 0;
    /// @brief 購読しているSubscriptionの購読を解除します。
    virtual bool Unsubscribe(const std::string& subscription_id) = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_LOCAL_ROOM_MEMBER_HPP */
