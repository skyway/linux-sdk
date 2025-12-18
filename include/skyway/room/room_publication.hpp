//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_ROOM_PUBLICATION_HPP
#define SKYWAY_ROOM_ROOM_PUBLICATION_HPP

#include <skyway/core/interface/publication.hpp>

#include "skyway/room/interface/room_domain_factory.hpp"
#include "skyway/room/interface/room_publication.hpp"

namespace skyway {
namespace room {

/// @brief RoomPublicationの操作を行うクラス
class RoomPublication : public interface::RoomPublication,
                        public core::interface::Publication::EventListener {
public:
    RoomPublication(std::shared_ptr<core::interface::Publication> core,
                    interface::RoomDomainFactory* factory);
    ~RoomPublication();
    std::string Id() override;
    std::shared_ptr<interface::RoomMember> Publisher() override;
    std::vector<std::shared_ptr<interface::RoomSubscription>> Subscriptions() override;
    model::ContentType ContentType() override;
    std::optional<std::string> Metadata() override;
    std::vector<model::Codec> CodecCapabilities() override;
    std::vector<model::Encoding> Encodings() override;
    core::interface::PublicationState State() override;
    std::shared_ptr<core::interface::LocalStream> Stream() override;
    void AddEventListener(interface::RoomPublication::EventListener* listener) override;
    void RemoveEventListener(interface::RoomPublication::EventListener* listener) override;
    bool UpdateMetadata(const std::string& metadata) override;
    bool UpdateEncodings(std::vector<model::Encoding> encodings) override;
    bool ReplaceStream(std::shared_ptr<core::interface::LocalStream> stream) override;
    bool Cancel() override;
    bool Enable() override;
    bool Disable() override;
    std::optional<model::WebRTCStats> GetStats(const std::string& selector) override;

private:
    // core::interface::Publication::EventListener
    void OnUnpublished() override;
    void OnSubscribed(std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnUnsubscribed(std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnSubscriptionListChanged() override;
    void OnMetadataUpdated(const std::string& metadata) override;
    void OnEnabled() override;
    void OnDisabled() override;
    void OnStateChanged() override;
    void OnConnectionStateChanged(const core::ConnectionState new_state) override;

    std::shared_ptr<core::interface::Publication> core_;
    interface::RoomDomainFactory* factory_;

    std::mutex listener_mtx_;
    interface::RoomPublication::EventListener* listener_;
};

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ROOM_PUBLICATION_HPP */
