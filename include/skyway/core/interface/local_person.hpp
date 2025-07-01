//
//  local_person.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/08/04.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_LOCAL_PERSON_HPP_
#define SKYWAY_CORE_INTERFACE_LOCAL_PERSON_HPP_

#include "skyway/analytics/interface/analytics_client.hpp"
#include "skyway/core/interface/chunk_messenger.hpp"
#include "skyway/core/interface/local_stream.hpp"
#include "skyway/core/interface/publication.hpp"
#include "skyway/core/interface/remote_member.hpp"

namespace skyway {
namespace core {
namespace interface {

/// @brief LocalPersonのインターフェース
class LocalPerson : public Member {
public:
    /// @brief イベントリスナ
    class EventListener : public Member::EventListener {
    public:
        /// @brief このLocalPersonがPublishした時に発火するイベント
        virtual void OnStreamPublished(std::shared_ptr<interface::Publication> publication) {}
        /// @brief このLocalPersonがUnpublishした時に発火するイベント
        virtual void OnStreamUnpublished(std::shared_ptr<interface::Publication> publication) {}
        /// @brief このLocalPersonがSubscribeした時に発火するイベント
        /// @param subscription 対象のSubscription。まだstreamがsetされていない可能性があります。
        virtual void OnPublicationSubscribed(std::shared_ptr<interface::Subscription> subscription) {}
        /// @brief このLocalPersonがUnsubscribeした時に発火するイベント
        virtual void OnPublicationUnsubscribed(std::shared_ptr<interface::Subscription> subscription) {}
    };
    /// @brief `Publish`でPublicationに対して指定するオプション
    struct PublicationOptions {
        /// @brief metadata
        std::optional<std::string> metadata;
        /// @brief コーデック一覧
        std::vector<model::Codec> codec_capabilities;
        /// @brief エンコーディング設定
        std::vector<model::Encoding> encodings;
        /// @brief `Publish`時の公開状態
        bool is_enabled;

        PublicationOptions(bool is_enabled = true) : is_enabled(is_enabled) {}
    };
    /// @brief `Subscribe`でSubscriptionに対して指定するオプション
    struct SubscriptionOptions {
        /// @brief `Subscribe`時の購読状態
        bool is_enabled;
        /// @brief 優先エンコーディングID
        std::optional<std::string> preferred_encoding_id;
        SubscriptionOptions(bool is_enabled = true) : is_enabled(is_enabled) {}
    };
    virtual ~LocalPerson() = default;

    /// @cond INTERNAL_SECTION
    virtual ChunkMessenger* Messenger() const = 0;

    virtual analytics::interface::AnalyticsClient* AnalyticsClient() const = 0;
    /// @endcond

    /// @brief Streamを公開します。
    /// @param stream 公開するStream
    /// @param options Publicationに指定するオプション
    virtual std::shared_ptr<interface::Publication> Publish(std::shared_ptr<LocalStream> stream,
                                 PublicationOptions options) = 0;

    /// @brief 公開されているPublicationを購読します。
    /// @param publication_id 公開されているPublicationのId
    /// @param options Subscriptionに指定するオプション
    virtual std::shared_ptr<interface::Subscription> Subscribe(const std::string& publication_id,
                                    const SubscriptionOptions& options) = 0;

    /// @brief 公開しているPublicationを非公開にします。
    /// @param publication_id 公開しているPublicationのId
    virtual bool Unpublish(const std::string& publication_id) const = 0;

    /// @brief 購読しているSubscriptionの購読を解除します。
    /// @param subscription_id 公開しているSubscriptionのId
    virtual bool Unsubscribe(const std::string& subscription_id) const = 0;

    /// @cond INTERNAL_SECTION
    // These event functions are invoked by local person's action after receiving success message
    // from RTC-API server
    virtual void OnPublished(std::shared_ptr<interface::Publication> publication)                               = 0;
    virtual void OnUnpublished(std::shared_ptr<interface::Publication> publication)                             = 0;
    virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription, std::shared_ptr<interface::RemoteMember> publisher)   = 0;
    virtual void OnUnsubscribed(std::shared_ptr<interface::Subscription> subscription, std::shared_ptr<interface::RemoteMember> publisher) = 0;

    // These event functions are invoked by remote member
    virtual void OnPublicationSubscribedByRemoteMember(std::shared_ptr<interface::Subscription> subscription,
                                                       std::shared_ptr<interface::RemoteMember> subscriber)   = 0;
    virtual void OnPublicationUnsubscribedByRemoteMember(std::shared_ptr<interface::Subscription> subscription,
                                                         std::shared_ptr<interface::RemoteMember> subscriber) = 0;

    /// @brief LocalPersonインスタンスを無効にし、リソースを解放します。
    /// @details Dispose後のLocalPersonインスタンスは利用できません。
    virtual void Dispose() = 0;
    /// @endcond

protected:
    LocalPerson(std::shared_ptr<interface::Channel> channel, const model::Member& dto);
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_LOCAL_PERSON_HPP_ */
