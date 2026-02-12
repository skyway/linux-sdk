//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_P2P_P2P_ROOM_HPP
#define SKYWAY_ROOM_P2P_P2P_ROOM_HPP

#include "skyway/room/abstract/room.hpp"
#include "skyway/room/p2p/local_p2p_room_member.hpp"
#include "skyway/room/p2p/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace p2p {

/// @cond INTERNAL_SECTION
class P2PRoomFactory : public interface::RoomFactory {
public:
    std::shared_ptr<interface::Room> Create(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomDomainFactory> domain_factory) override;
    std::shared_ptr<interface::Room> Find(
        interface::RoomQuery query,
        std::unique_ptr<interface::RoomDomainFactory> domain_factory) override;
    std::shared_ptr<interface::Room> FindOrCreate(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomDomainFactory> domain_factory) override;
};
/// @endcond

/// @brief P2PRoomの操作を行うクラス
class P2PRoom : public abstract::Room, public std::enable_shared_from_this<P2PRoom> {
public:
    P2PRoom(std::shared_ptr<core::interface::Channel> channel,
            std::unique_ptr<interface::RoomDomainFactory> factory);
    interface::RoomType Type() override;
    /// @brief P2PRoomに存在するPublicationを取得します。
    std::vector<std::shared_ptr<interface::RoomPublication>> Publications() override;
    /// @brief P2PRoomに存在するSubscriptionを取得します。
    std::vector<std::shared_ptr<interface::RoomSubscription>> Subscriptions() override;
    /// @brief P2PRoomに存在するMemberを取得します。
    std::vector<std::shared_ptr<interface::RoomMember>> Members() override;

    /// @brief P2PRoomを作成します。
    static std::shared_ptr<P2PRoom> Create(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<P2PRoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief P2PRoomを作成します。
    static std::shared_ptr<P2PRoom> Create();
    /// @brief P2PRoomの検索をします。
    static std::shared_ptr<P2PRoom> Find(
        interface::RoomQuery query,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<P2PRoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief P2PRoomの検索をし、存在しなければ作成します。
    static std::shared_ptr<P2PRoom> FindOrCreate(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<P2PRoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief P2PRoomへ参加します。
    std::shared_ptr<LocalP2PRoomMember> Join(interface::RoomMemberInitOptions options);

protected:
    // core::interface::Channel::EventListener
    void OnMemberListChanged() override;
    void OnMemberJoined(std::shared_ptr<core::interface::Member> member) override;
    void OnMemberLeft(std::shared_ptr<core::interface::Member> member) override;
    void OnMemberMetadataUpdated(std::shared_ptr<core::interface::Member> member,
                                 const std::string& metadata) override;
    void OnPublicationMetadataUpdated(std::shared_ptr<core::interface::Publication> publication,
                                      const std::string& metadata) override;
    void OnPublicationListChanged() override;
    void OnStreamPublished(std::shared_ptr<core::interface::Publication> publication) override;
    void OnStreamUnpublished(std::shared_ptr<core::interface::Publication> publication) override;
    void OnPublicationEnabled(std::shared_ptr<core::interface::Publication> publication) override;
    void OnPublicationDisabled(std::shared_ptr<core::interface::Publication> publication) override;
    void OnSubscriptionListChanged() override;
    void OnPublicationSubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;
    void OnPublicationUnsubscribed(
        std::shared_ptr<core::interface::Subscription> subscription) override;

private:
    static std::shared_ptr<P2PRoom> CreateShared(
        std::shared_ptr<core::interface::Channel> channel,
        std::unique_ptr<interface::RoomDomainFactory> factory);

public:
    /// @cond INTERNAL_SECTION
    friend class P2PRoomFactory;
    friend class P2PRoomTest;
    friend class LocalP2PRoomMemberTest;
    /// @endcond
};

}  // namespace p2p
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_P2P_P2P_ROOM_HPP */
