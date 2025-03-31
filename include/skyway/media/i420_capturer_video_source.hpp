//
//  i420_capturer_video_source.hpp
//  skyway
//
//  Created by ogura on 2024/12/10.
//  Copyright © 2024 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_MEDIA_I420_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_I420_CAPTURER_VIDEO_SOURCE_HPP_

#include "skyway/media/interface/capturer_video_source.hpp"

namespace skyway {
namespace media {

/// I420形式となっている映像の描画処理を行うクラス
class I420CapturerVideoSource : public interface::CapturerVideoSource {
public:
    /// @cond INTERNAL_SECTION
    class I420InternalCapturerVideoSource : public interface::InternalCapturerVideoSource {
    public:
        ~I420InternalCapturerVideoSource();

        static rtc::scoped_refptr<I420InternalCapturerVideoSource> Create();

        void Render(int width,
                    int height,
                    const uint8_t* y,
                    const uint8_t* u,
                    const uint8_t* v,
                    int stride_y,
                    int stride_u,
                    int stride_v);
        bool is_screencast() const override;
        absl::optional<bool> needs_denoising() const override;
        webrtc::MediaSourceInterface::SourceState state() const override;
        bool remote() const override;
        void OnFrame(const webrtc::VideoFrame& frame) override;

    protected:
        I420InternalCapturerVideoSource();
    };
    /// @endcond
    I420CapturerVideoSource();
    ~I420CapturerVideoSource();

    /// @brief I420形式の画像を描画、送信します。
    void Render(int width,
                int height,
                const uint8_t* y,
                const uint8_t* u,
                const uint8_t* v,
                int stride_y,
                int stride_u,
                int stride_v);

    /// @cond INTERNAL_SECTION
    // Impl interface::InternalCapturerVideoSource
    rtc::scoped_refptr<interface::InternalCapturerVideoSource> GetSource();
    /// @endcond

private:
    rtc::scoped_refptr<I420InternalCapturerVideoSource> source_;
};
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_I420_CAPTURER_VIDEO_SOURCE_HPP_ */
