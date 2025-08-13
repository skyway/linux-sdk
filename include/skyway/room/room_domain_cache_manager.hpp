//
//  room_domain_cache_manager.hpp
//  skyway
//
//  Created by iorar on 2025/07/18.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_ROOM_ROOM_DOMAIN_CACHE_MANAGER_HPP
#define SKYWAY_ROOM_ROOM_DOMAIN_CACHE_MANAGER_HPP

#include <map>
#include <mutex>
#include <unordered_map>

#include "skyway/room/interface/room_domain_cache_manager.hpp"

namespace skyway {
namespace room {

/// @cond INTERNAL_SECTION
template <typename T>
class RoomDomainCacheManager : public interface::RoomDomainCacheManager<T> {
public:
    ~RoomDomainCacheManager();
    void CacheRoomDomainInstance(const std::string& id, std::shared_ptr<T> instance) override;
    std::shared_ptr<T> FindCachedRoomDomainInstance(const std::string& id) override;
    void RemoveCachedRoomDomainInstance(const std::string& id) override;

private:
    void ClearExpiredDeletedInstanceIds();
    std::mutex mtx_;
    std::unordered_map<std::string, std::shared_ptr<T>> cached_room_domain_instances_;

    // To prevent memory leaks, we keep track of deleted instances.
    // For efficient searching, two types of containers are used: search by ID and search by
    // time.
    std::unordered_map<std::string, std::chrono::steady_clock::time_point>
        deleted_room_domain_instance_ids_by_id_;
    std::multimap<std::chrono::steady_clock::time_point, std::string>
        deleted_room_domain_instance_ids_by_time_;

public:
    friend class RoomDomainCacheManagerTest;
};
/// @endcond

}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_ROOM_DOMAIN_CACHE_MANAGER_HPP */
