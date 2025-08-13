//
//  room_domain_cache_manager.hpp
//  skyway
//
//  Created by iorar on 2025/07/18.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_CACHE_MANAGER_HPP
#define SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_CACHE_MANAGER_HPP

#include <memory>
#include <string>

namespace skyway {
namespace room {
namespace interface {

/// @cond INTERNAL_SECTION
template <typename T>
class RoomDomainCacheManager {
public:
    virtual ~RoomDomainCacheManager() = default;

    virtual void CacheRoomDomainInstance(const std::string& id, std::shared_ptr<T> instance) = 0;
    virtual std::shared_ptr<T> FindCachedRoomDomainInstance(const std::string& id)           = 0;
    virtual void RemoveCachedRoomDomainInstance(const std::string& id)                       = 0;
};
/// @endcond

}  // namespace interface
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_INTERFACE_ROOM_DOMAIN_CACHE_MANAGER_HPP */
