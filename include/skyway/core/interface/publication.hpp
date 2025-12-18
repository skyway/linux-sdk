//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_PUBLICATION_HPP_
#define SKYWAY_CORE_INTERFACE_PUBLICATION_HPP_

#include "skyway/core/connection_state.hpp"
#include "skyway/core/interface/local_media_stream.hpp"
#include "skyway/core/interface/local_stream.hpp"
#include "skyway/core/interface/member.hpp"
#include "skyway/core/interface/subscription.hpp"

namespace skyway {
namespace core {
namespace interface {

using LocalStream     = interface::LocalStream;

/// @brief Publicationの状態
enum class PublicationState { kEnabled, kDisabled, kCanceled };

/// @brief Publicationのインターフェース
// `std::enable_shared_from_this<T>` is supposed to be inherited by concrete classes.
// (e.g. skyway/core/publication.hpp)
// however if so, compile failed on the Android SDK that includes interfaces.
class Publication : public std::enable_shared_from_this<Publication>, public ConnectionStateChangeNotifiable {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        /// @deprecated 本機能は非推奨です。
        /// @brief このPublicationがUnpublishされた時に発火するイベント
        [[deprecated]] virtual void OnUnpublished() {}
        /// @brief このPublicationがSubscribeされた時に発火するイベント
        /// @param subscription 対象のSubscription。まだstreamがsetされていない可能性があります。
        virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription) {}
        /// @brief このPublicationがUnsubscribeされた時に発火するイベント
        virtual void OnUnsubscribed(std::shared_ptr<interface::Subscription> subscription) {}
        /// @brief このPublicationに対するSubscriptionの数が変更された時に発火するイベント
        virtual void OnSubscriptionListChanged() {}
        /// @brief このPublicationのMetadataが変化した時に発火するイベント
        virtual void OnMetadataUpdated(const std::string& metadata) {}
        /// @brief このPublicationの通信が有効になった時に発火するイベント。
        /// Publication.Enableが実行された時に発火します。
        virtual void OnEnabled() {}
        /// @brief このPublicationの通信が無効になった時に発火するイベント。
        /// Publication.Disableが実行された時に発火します。
        virtual void OnDisabled() {}
        /// @brief このPublicationのStateが変化した時に発火するイベント
        virtual void OnStateChanged() {}
        /// @brief このPublicationのメディア通信の状態が変化した時に発火するイベント
        virtual void OnConnectionStateChanged(const core::ConnectionState new_state) {}
    };
    /// @cond INTERNAL_SECTION
    class InternalListener {
    public:
        virtual void OnEncodingsUpdated(std::shared_ptr<interface::Publication> publication,
                                        std::vector<model::Encoding> encodings) {}
        virtual void OnStreamReplaced(std::shared_ptr<interface::Publication> publication,
                                      std::shared_ptr<LocalMediaStream> stream) {}
        virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription) {}
    };
    class Callback {
    public:
        virtual const std::optional<nlohmann::json> GetStatsReport(std::shared_ptr<interface::Publication> publication) = 0;
    };
    /// @endcond
    virtual ~Publication() = default;

    /// @brief イベントを購読します。
    /// @param listener イベントリスナ
    virtual void AddEventListener(EventListener* listener) = 0;
    /// @brief イベントの購読を中止します。
    /// @param listener 対象のイベントリスナ
    virtual void RemoveEventListener(EventListener* listener) = 0;
    /// @cond INTERNAL_SECTION
    virtual void AddInternalListener(InternalListener* listener)    = 0;
    virtual void RemoveInternalListener(InternalListener* listener) = 0;
    /// @endcond

    /// @brief Idを取得します。
    virtual std::string Id() const = 0;
    /// @brief このPublicationをPublishしているMemberを取得します。
    virtual std::shared_ptr<interface::Member> Publisher() const = 0;
    /// @brief このPublicationを購読しているSubsciptionの一覧を取得します。
    virtual std::vector<std::shared_ptr<interface::Subscription>> Subscriptions() const = 0;
    virtual model::PublicationType Type() const = 0;
    /// @brief ContentType(VideoかAudioかDataか)を取得します。
    virtual model::ContentType ContentType() const = 0;
    /// @brief Metadataを取得します。
    virtual std::optional<std::string> Metadata() const = 0;
    /// @brief このPublicationのOriginを取得します。
    virtual std::shared_ptr<interface::Publication> Origin() const = 0;
    /// @brief このPublicationのコーデック一覧を取得します。
    virtual std::vector<model::Codec> CodecCapabilities() const = 0;
    /// @brief このPublicationのエンコーディング設定の一覧を取得します。
    virtual std::vector<model::Encoding> Encodings() const = 0;
    /// @brief State(公開状態がEnableかDisabelかCancelか)を取得します。
    virtual PublicationState State() = 0;

    // Publisher(LocalPerson) only has this pointer
    /// @brief Publisherが持つStreamを取得します。
    virtual std::shared_ptr<LocalStream> Stream() const = 0;

    /// @brief Metadataを更新します。
    virtual bool UpdateMetadata(const std::string& metadata) = 0;
    /// @brief エンコーディング設定を更新します。
    virtual bool UpdateEncodings(std::vector<model::Encoding> encodings) = 0;
    /// @brief 公開しているStreamを変更します。
    virtual bool ReplaceStream(std::shared_ptr<LocalStream> stream) = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief Publishを中止します。
    [[deprecated]] virtual bool Cancel() const = 0;
    /// @brief Publicationの公開を開始します。disableによって停止していた場合は再開します。
    virtual bool Enable() = 0;
    /// @brief Publicationの公開を一時停止します。
    virtual bool Disable() const = 0;
    /// @deprecated 本機能は非推奨です。
    /// @brief 統計情報を取得します。
    /// @param selector 取得対象のmemberID
    [[deprecated]] virtual std::optional<model::WebRTCStats> GetStats(
        const std::string& selector) = 0;
    /// @cond INTERNAL_SECTION
    virtual void AddGetStatsCallback(const std::string& remote_member_id, Callback* callback) = 0;
    virtual void RemoveGetStatsCallback(const std::string& remote_member_id)                  = 0;
    /// @endcond

    /// @cond INTERNAL_SECTION
    // Do not wrap below APIs
    virtual void SetCodecCapabilities(std::vector<model::Codec> codec_capabilities) = 0;
    virtual void SetEncodings(std::vector<model::Encoding> encodings)               = 0;
    virtual void SetStream(std::shared_ptr<LocalStream> stream)                     = 0;
    virtual bool IsEnabling()                                                       = 0;
    virtual void Dispose()                                                          = 0;

    virtual void OnUnpublished()                                = 0;
    virtual void OnSubscribed(std::shared_ptr<interface::Subscription> subscription)       = 0;
    virtual void OnUnsubscribed(std::shared_ptr<interface::Subscription> subscription)     = 0;
    virtual void OnMetadataUpdated(const std::string& metadata) = 0;
    virtual void OnEnabled()                                    = 0;
    virtual void OnDisabled()                                   = 0;
    /// @endcond
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_PUBLICATION_HPP_ */
