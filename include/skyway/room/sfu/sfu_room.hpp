//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_SFU_SFU_ROOM_HPP
#define SKYWAY_ROOM_SFU_SFU_ROOM_HPP

#include <skyway/plugin/sfu_bot_plugin/sfu_bot.hpp>

#include "skyway/room/abstract/room.hpp"
#include "skyway/room/sfu/local_sfu_room_member.hpp"
#include "skyway/room/sfu/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace sfu {

/// @cond INTERNAL_SECTION
class SFURoomFactory : public interface::RoomFactory {
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

/// @brief SFURoomの操作を行うクラス
class SFURoom : public abstract::Room, public std::enable_shared_from_this<SFURoom> {
public:
    SFURoom(std::shared_ptr<core::interface::Channel> channel,
            std::unique_ptr<interface::RoomDomainFactory> factory);
    interface::RoomType Type() override;

    /// @brief SFURoomに存在するPublicationを取得します。
    std::vector<std::shared_ptr<interface::RoomPublication>> Publications() override;
    /// @brief SFURoomに存在するSubscriptionを取得します。
    std::vector<std::shared_ptr<interface::RoomSubscription>> Subscriptions() override;
    /// @brief SFURoomに存在するMemberを取得します
    std::vector<std::shared_ptr<interface::RoomMember>> Members() override;

    /// @brief SFURoomを作成します。
    static std::shared_ptr<SFURoom> Create(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<SFURoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief SFURoomを作成します。
    static std::shared_ptr<SFURoom> Create();
    /// @brief SFURoomの検索をします。
    static std::shared_ptr<SFURoom> Find(
        interface::RoomQuery query,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<SFURoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief SFURoomの検索をし、存在しなければ作成します。
    static std::shared_ptr<SFURoom> FindOrCreate(
        interface::RoomInitOptions options,
        std::unique_ptr<interface::RoomFactory> room_factory = std::make_unique<SFURoomFactory>(),
        std::unique_ptr<interface::RoomDomainFactory> domain_factory =
            std::make_unique<RoomDomainFactory>());
    /// @brief SFURoomへ参加します。
    std::shared_ptr<LocalSFURoomMember> Join(interface::RoomMemberInitOptions options);

    /// @cond INTERNAL_SECTION
    std::shared_ptr<plugin::sfu_bot::SfuBot> GetSFUBot();
    /// @endcond

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
    static std::shared_ptr<SFURoom> CreateShared(
        std::shared_ptr<core::interface::Channel> channel,
        std::unique_ptr<interface::RoomDomainFactory> factory);

public:
    /// @cond INTERNAL_SECTION
    friend class SFURoomFactory;
    friend class SFURoomTest;
    friend class LocalSFURoomMemberTest;
    /// @endcond
};

}  // namespace sfu
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_SFU_SFU_ROOM_HPP */
