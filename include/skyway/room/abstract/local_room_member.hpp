//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_ABSTRACT_LOCAL_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_ABSTRACT_LOCAL_ROOM_MEMBER_HPP

#include <mutex>

#include <skyway/core/interface/local_person.hpp>

#include "skyway/room/abstract/room_member.hpp"
#include "skyway/room/interface/local_room_member.hpp"
#include "skyway/room/interface/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace abstract {

/// @brief LocalRoomMemberの操作を行う抽象クラス
class LocalRoomMember : public abstract::RoomMember, public interface::LocalRoomMember {
public:
    virtual ~LocalRoomMember();

    /// @brief イベントの購読します。
    void AddEventListener(interface::LocalRoomMember::EventListener* listener) override;

    /// @brief イベントの購読を中止します。
    void RemoveEventListener(interface::LocalRoomMember::EventListener* listener) override;

protected:
    /// @cond INTERNAL_SECTION
    class CoreEventListenerAdapter : public core::interface::LocalPerson::EventListener {
    public:
        CoreEventListenerAdapter(LocalRoomMember* outer);
        void OnStreamPublished(std::shared_ptr<core::interface::Publication> publication) override;
        void OnStreamUnpublished(
            std::shared_ptr<core::interface::Publication> publication) override;
        void OnPublicationSubscribed(
            std::shared_ptr<core::interface::Subscription> subscription) override;
        void OnPublicationUnsubscribed(
            std::shared_ptr<core::interface::Subscription> subscription) override;
        void OnLeft() override;
        void OnMetadataUpdated(const std::string& metadata) override;
        void OnPublicationListChanged() override;
        void OnSubscriptionListChanged() override;

    private:
        LocalRoomMember* outer_;
    };

    LocalRoomMember(std::shared_ptr<core::interface::LocalPerson> core,
                    std::shared_ptr<interface::Room> room,
                    interface::RoomDomainFactory* factory);

    core::interface::LocalPerson::PublicationOptions ConvertToCorePublicationOptions(
        const interface::LocalRoomMember::PublicationOptions& options);
    core::interface::LocalPerson::SubscriptionOptions ConvertToCoreSubscriptionOptions(
        const interface::LocalRoomMember::SubscriptionOptions& options);
    model::PublicationType ConvertToCorePublicationType(domain::PublicationType type);
    /// @endcond

private:
    void OnStreamPublished(std::shared_ptr<core::interface::Publication> publication);
    void OnStreamUnpublished(std::shared_ptr<core::interface::Publication> publication);
    void OnPublicationSubscribed(std::shared_ptr<core::interface::Subscription> subscription);
    void OnPublicationUnsubscribed(std::shared_ptr<core::interface::Subscription> subscription);
    void OnLeft();
    void OnMetadataUpdated(const std::string& metadata);
    void OnPublicationListChanged();
    void OnSubscriptionListChanged();

    std::unique_ptr<CoreEventListenerAdapter> core_event_listener_adapter_;
    std::mutex listener_mtx_;
    interface::LocalRoomMember::EventListener* listener_;
};

}  // namespace abstract
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ABSTRACT_LOCAL_ROOM_MEMBER_HPP */
