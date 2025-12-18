//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_MEMBER_HPP_
#define SKYWAY_CORE_INTERFACE_MEMBER_HPP_

#include <atomic>
#include <mutex>
#include <string>
#include <unordered_set>

#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class Channel;
class Publication;
class Subscription;

/// @brief Memberの入室状態
enum class MemberState { kJoined, kLeft };

/// @brief LocalPersonおよびRemoteMemberの基底クラス
class Member: public std::enable_shared_from_this<Member> {
public:
    /// @brief イベントリスナ
    class EventListener {
    public:
        /// @brief MemberがChannelから退出した時に発火するイベント
        virtual void OnLeft() {}
        /// @brief MemberのMetadataが更新した時に発火するイベント
        virtual void OnMetadataUpdated(const std::string& metadata) {}
        /// @brief MemberのPublicationの一覧が更新した時に発火するイベント
        virtual void OnPublicationListChanged() {}
        /// @brief MemberのSubscriptionの一覧が更新した時に発火するイベント
        virtual void OnSubscriptionListChanged() {}
    };
    virtual ~Member() = default;

    /// @brief イベントを購読します。
    /// @param listener イベントリスナ
    void AddEventListener(EventListener* listener);
    /// @brief イベントの購読を中止します。
    /// @param listener 対象のイベントリスナ
    void RemoveEventListener(EventListener* listener);

    /// @brief Metadataを更新します
    bool UpdateMetadata(const std::string& metadata);
    /// @brief Channelから退室します。
    bool Leave();

    /// @brief Idを取得します。
    std::string Id() const;
    /// @brief Nameを取得します。
    std::optional<std::string> Name() const;
    /// @brief Metadataを取得します。
    std::optional<std::string> Metadata() const;
    /// @brief MemberTypeを取得します。
    model::MemberType Type() const;
    /// @brief Subtypeを取得します。
    std::string Subtype() const;
    /// @brief Side(LocalかRemoteか)を取得します。
    model::Side Side() const;
    /// @brief State(Memberの入室状態)を取得します。
    MemberState State() const;

    /// @brief 自身が持つ全てのPublicationを取得します。
    std::vector<std::shared_ptr<interface::Publication>> Publications() const;
    /// @brief 自身が持つ全てのSubscriptionを取得します。
    std::vector<std::shared_ptr<interface::Subscription>> Subscriptions() const;

    /// @cond INTERNAL_SECTION
    virtual void OnLeft();
    void OnMetadataUpdated(const std::string& metadata);
    virtual void OnPublicationListChanged();
    virtual void OnSubscriptionListChanged();
    /// @endcond

protected:
    Member(std::shared_ptr<interface::Channel> channel, const model::Member& initial_dto, const model::Side& side);

    std::weak_ptr<interface::Channel> channel_;
    model::Member initial_dto_;
    model::Side side_;
    MemberState state_;
    std::mutex listeners_mtx_;
    std::unordered_set<EventListener*> listeners_;
    std::atomic<bool> metadata_updated_;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_MEMBER_HPP_ */
