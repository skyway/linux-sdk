//
//  room_member.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/11/21.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_MEMBER_HPP

#include <skyway/core/interface/member.hpp>

namespace skyway {
namespace room {
namespace interface {

class Room;
class RoomPublication;
class RoomSubscription;

/// @brief RoomMemberの操作を行うインターフェース
class RoomMember {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        virtual ~EventListener() = default;
        /// @brief Memberが退出した後に発生するイベント
        virtual void OnLeft() {}

        /// @brief このRoomMemberのMetadataが更新された後に発生するイベント
        /// @param metadata Metadata
        virtual void OnMetadataUpdated(const std::string& metadata) {}

        /// @brief このRoomMemberのPublicationの数が変化された後に発生するイベント
        virtual void OnPublicationListChanged() {}

        /// @brief このRoomMemberのSubscriptionの数が変化された後に発生するイベント
        virtual void OnSubscriptionListChanged() {}
    };
    virtual ~RoomMember() = default;
    /// @brief このMemberに紐づくRoomのIdを取得します。
    virtual std::optional<std::string> RoomId() = 0;
    /// @brief このMemberに紐づくRoomのNameを取得します。
    virtual std::optional<std::string> RoomName() = 0;
    /// @brief Idを取得します。
    virtual std::string Id() = 0;
    /// @brief Nameを取得します。
    virtual std::optional<std::string> Name() = 0;
    /// @brief Metadataを取得します。
    virtual std::optional<std::string> Metadata() = 0;
    /// @brief Typeを取得します。
    virtual model::MemberType Type() = 0;
    /// @brief SubTypeを取得します。
    virtual std::string Subtype() = 0;
    /// @brief Sideを取得します。
    virtual model::Side Side() = 0;
    /// @brief Stateを取得します。
    virtual core::interface::MemberState State() = 0;

    /// @brief このMemberのPublication一覧を取得します。
    virtual std::vector<std::shared_ptr<RoomPublication>> Publications() = 0;
    /// @brief このMemberのSubscription一覧を取得します。
    virtual std::vector<std::shared_ptr<RoomSubscription>> Subscriptions() = 0;

    /// @brief Metadataを更新します。
    virtual bool UpdateMetadata(const std::string& metadata) = 0;
    /// @brief Roomから退室します。
    virtual bool Leave() = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_MEMBER_HPP */
