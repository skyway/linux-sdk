//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_ROOM_PUBLICATION_HPP
#define SKYWAY_ROOM_ROOM_PUBLICATION_HPP

#include <mutex>

#include <skyway/core/interface/publication.hpp>

#include "skyway/media/stream/interface/local/local_stream.hpp"
#include "skyway/room/interface/room_domain_factory.hpp"
#include "skyway/room/interface/room_publication.hpp"

namespace skyway {
namespace room {

/// @brief RoomPublicationの操作を行うクラス
class RoomPublication : public interface::RoomPublication {
public:
    /// @cond INTERNAL_SECTION
    RoomPublication(std::shared_ptr<core::interface::Publication> core,
                    interface::RoomDomainFactory* factory,
                    std::shared_ptr<media::stream::interface::local::LocalStream> stream);
    /// @endcond

    ~RoomPublication();
    std::string Id() override;
    domain::PublicationType Type() override;
    std::shared_ptr<interface::RoomMember> Publisher() override;
    std::vector<std::shared_ptr<interface::RoomSubscription>> Subscriptions() override;
    domain::ContentType ContentType() override;
    std::optional<std::string> Metadata() override;
    std::vector<Codec> CodecCapabilities() override;
    std::vector<Encoding> Encodings() override;
    PublicationState State() override;
    std::shared_ptr<media::stream::interface::local::LocalStream> Stream() override;
    void AddEventListener(interface::RoomPublication::EventListener* listener) override;
    void RemoveEventListener(interface::RoomPublication::EventListener* listener) override;
    bool UpdateMetadata(const std::string& metadata) override;
    bool UpdateEncodings(std::vector<Encoding> encodings) override;
    bool ReplaceStream(
        std::shared_ptr<media::stream::interface::local::LocalStream> stream) override;
    bool Enable() override;
    bool Disable() override;
    std::optional<WebRTCStats> GetStats(const std::string& selector) override;

private:
    class CoreEventListenerAdapter : public core::interface::Publication::EventListener {
    public:
        CoreEventListenerAdapter(RoomPublication* outer);
        void OnUnpublished();
        void OnSubscribed(std::shared_ptr<core::interface::Subscription> subscription);
        void OnUnsubscribed(std::shared_ptr<core::interface::Subscription> subscription);
        void OnSubscriptionListChanged();
        void OnMetadataUpdated(const std::string& metadata);
        void OnEnabled();
        void OnDisabled();
        void OnStateChanged();
        void OnConnectionStateChanged(const core::ConnectionState new_state);

    private:
        RoomPublication* outer_;
    };

    class OriginEventListenerAdapter : public core::interface::Publication::EventListener {
    public:
        OriginEventListenerAdapter(RoomPublication* outer);
        void OnMetadataUpdated(const std::string& metadata) override;

    private:
        RoomPublication* outer_;
    };

    void OnUnpublished();
    void OnSubscribed(std::shared_ptr<core::interface::Subscription> subscription);
    void OnUnsubscribed(std::shared_ptr<core::interface::Subscription> subscription);
    void OnSubscriptionListChanged();
    void OnMetadataUpdated(const std::string& metadata);
    void OnEnabled();
    void OnDisabled();
    void OnStateChanged();
    void OnConnectionStateChanged(const core::ConnectionState new_state);
    void SetStream(std::shared_ptr<media::stream::interface::local::LocalStream> stream);
    domain::PublicationType ConvertToPlatformPublicationType(model::PublicationType type);
    PublicationState ConvertToPlatformPublicationState(core::interface::PublicationState state);
    std::mutex stream_mtx_;
    std::shared_ptr<media::stream::interface::local::LocalStream> stream_;
    std::shared_ptr<core::interface::Publication> core_;
    interface::RoomDomainFactory* factory_;
    std::unique_ptr<CoreEventListenerAdapter> core_event_listener_adapter_;

    std::mutex listener_mtx_;
    interface::RoomPublication::EventListener* listener_;
    std::unique_ptr<OriginEventListenerAdapter> origin_event_listener_adapter_;
};

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ROOM_PUBLICATION_HPP */
