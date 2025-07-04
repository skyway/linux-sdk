//
//  room_member.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2023/12/01.
//  Copyright © 2023 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_ABSTRACT_ROOM_MEMBER_HPP
#define SKYWAY_ROOM_ABSTRACT_ROOM_MEMBER_HPP

#include <skyway/room/interface/room_member.hpp>

#include "skyway/room/interface/room_domain_factory.hpp"

namespace skyway {
namespace room {
namespace abstract {

/// @brief RoomMemberの操作を行う抽象クラス
class RoomMember : public virtual interface::RoomMember {
public:
    virtual ~RoomMember();

    std::optional<std::string> RoomId() override;
    std::optional<std::string> RoomName() override;
    std::string Id() override;
    std::optional<std::string> Name() override;
    std::optional<std::string> Metadata() override;
    model::MemberType Type() override;
    std::string Subtype() override;
    model::Side Side() override;
    core::interface::MemberState State() override;

    std::vector<std::shared_ptr<interface::RoomPublication>> Publications() override;
    std::vector<std::shared_ptr<interface::RoomSubscription>> Subscriptions() override;

    bool UpdateMetadata(const std::string& metadata) override;
    bool Leave() override;

protected:
    RoomMember(std::shared_ptr<core::interface::Member> core,
               std::shared_ptr<interface::Room> room,
               interface::RoomDomainFactory* factory);

    std::shared_ptr<core::interface::Member> core_;
    std::weak_ptr<interface::Room> room_;
    interface::RoomDomainFactory* factory_;
};

}  // namespace abstract
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ABSTRACT_ROOM_MEMBER_HPP */
