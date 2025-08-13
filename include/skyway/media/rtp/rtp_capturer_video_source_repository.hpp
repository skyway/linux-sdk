//
//  rtp_capturer_video_source_repository.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2025/06/30.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_RTP_RTP_CAPTURER_VIDEO_SOURCE_REPOSITORY_HPP_
#define SKYWAY_MEDIA_RTP_RTP_CAPTURER_VIDEO_SOURCE_REPOSITORY_HPP_

#include <mutex>
#include <unordered_set>

#include "skyway/media/rtp/interface/rtp_capturer_video_source_repository.hpp"

namespace skyway {
namespace media {
namespace rtp {

/// @cond INTERNAL_SECTION
class RtpCapturerVideoSourceRepository : public interface::RtpCapturerVideoSourceRepository {
public:
    ~RtpCapturerVideoSourceRepository();

    static std::shared_ptr<interface::RtpCapturerVideoSourceRepository> GetInstance();
    std::optional<uint16_t> Register(
        std::shared_ptr<interface::RtpCapturerVideoSource> video_source) override;
    bool Unregister(std::shared_ptr<interface::RtpCapturerVideoSource> video_source) override;
    std::shared_ptr<interface::RtpCapturerVideoSource> Find(const int& frame_id) override;
    static void Release();

private:
    RtpCapturerVideoSourceRepository();
    bool IsValidSource(
        const std::shared_ptr<interface::RtpCapturerVideoSource>& video_source) const;

    mutable std::mutex video_sources_mtx_;
    std::unordered_set<std::shared_ptr<interface::RtpCapturerVideoSource>> video_sources_;
    inline static std::mutex instance_mtx_;
    inline static std::shared_ptr<interface::RtpCapturerVideoSourceRepository> instance_ = nullptr;
    uint16_t current_frame_id_;

public:
    friend class RtpCapturerVideoSourceRepositoryTest;
};
/// @endcond

}  // namespace rtp
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_RTP_RTP_CAPTURER_VIDEO_SOURCE_REPOSITORY_HPP_ */
