//
//  room_publication.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/11/21.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_PUBLICATION_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_PUBLICATION_HPP

#include <skyway/core/interface/publication.hpp>

#include "skyway/room/interface/room_member.hpp"
#include "skyway/room/interface/room_subscription.hpp"

namespace skyway {
namespace room {
namespace interface {

/// @brief RoomのPublicationを操作するインタフェース
class RoomPublication {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        virtual ~EventListener() = default;
        /// @deprecated 本機能は非推奨です。
        /// @brief Unpublishされた後に発生するイベント
        [[deprecated]] virtual void OnUnpublished() {}

        /// @brief このPublicationがSubscribeされた後に発生するイベント
        /// @param subscription RoomSubscription
        virtual void OnSubscribed(std::shared_ptr<RoomSubscription> subscription) {}

        /// @brief このPublicationがUnsubscribeされた後に発生するイベント
        /// @param subscription RoomSubscription
        virtual void OnUnsubscribed(std::shared_ptr<RoomSubscription> subscription) {}

        /// @brief このPublicationに紐づくSubscriptionの数が変化した後に発生するイベント
        virtual void OnSubscriptionListChanged() {}

        /// @brief Metadataが更新された後に発生するイベント
        /// @param metadata 更新後のMetadata
        virtual void OnMetadataUpdated(const std::string& metadata) {}

        /// @brief Publicationが有効状態に変化した後にコールされるイベント
        virtual void OnEnabled() {}

        /// @brief Publicationが無効状態に変化した後にコールされるイベント
        virtual void OnDisabled() {}

        /// @brief Publicationの状態(Enabled, Disabled, Canceled)が変化した後にコールされるイベント
        virtual void OnStateChanged() {}

        /// @brief Publicationの接続状態が変化した後にコールされるイベント
        /// @param new_state 接続状態
        virtual void OnConnectionStateChanged(const core::ConnectionState new_state) {}
    };
    virtual ~RoomPublication() = default;
    /// @brief Idを取得します。
    virtual std::string Id() = 0;
    /// @brief このPublicationを公開しているMemberを取得します。
    virtual std::shared_ptr<RoomMember> Publisher() = 0;
    /// @brief このPublicationを購読しているSubsciptionの一覧を取得します。
    virtual std::vector<std::shared_ptr<RoomSubscription>> Subscriptions() = 0;
    /// @brief ContentType(VideoかAudioかDataか)を取得します。
    virtual model::ContentType ContentType() = 0;
    /// @brief Metadataを取得します。
    virtual std::optional<std::string> Metadata() = 0;
    /// @brief このPublicationのコーデック一覧を取得します。
    virtual std::vector<model::Codec> CodecCapabilities() = 0;
    /// @brief このPublicationのエンコーディング設定の一覧を取得します。
    virtual std::vector<model::Encoding> Encodings() = 0;
    /// @brief State(公開状態がEnableかDisabelかCancelか)を取得します。
    virtual core::interface::PublicationState State() = 0;
    /// @brief Publisherが持つStreamを取得します。
    virtual std::shared_ptr<core::interface::LocalStream> Stream() = 0;
    /// @brief イベントを購読します。
    virtual void AddEventListener(EventListener* listener) = 0;
    /// @brief イベントの購読を中止します。
    virtual void RemoveEventListener(EventListener* listener) = 0;
    /// @brief Metadataを更新します。
    virtual bool UpdateMetadata(const std::string& metadata) = 0;
    /// @brief エンコーディング設定を更新します。
    /// @details
    /// この機能はRTP映像入力モードでは機能しません。
    virtual bool UpdateEncodings(std::vector<model::Encoding> encodings) = 0;
    /// @brief 公開しているStreamを変更します。
    virtual bool ReplaceStream(std::shared_ptr<core::interface::LocalStream> stream) = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief 統計情報を取得します。
    /// @details 試験的なAPIです。今後インターフェースや仕様が変更される可能性があります。
    /// @param selector 取得対象のmemberID
    [[deprecated]] virtual std::optional<model::WebRTCStats> GetStats(
        const std::string& selector) = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief Publishを中止します。
    [[deprecated]] virtual bool Cancel() = 0;
    /// @brief Publicationの公開を開始します。disableによって停止していた場合は再開します。
    virtual bool Enable() = 0;
    /// @brief Publicationの公開を一時停止します。
    virtual bool Disable() = 0;
};

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_PUBLICATION_HPP */
