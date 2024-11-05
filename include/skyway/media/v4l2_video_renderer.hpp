//
//  v4l2_video_renderer.hpp
//  skyway
//
//  Created by iorar on 2023/12/19.
//  Copyright © 2023 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_MEDIA_V4L2_VIDEO_RENDERER_HPP_
#define SKYWAY_MEDIA_V4L2_VIDEO_RENDERER_HPP_

#include "skyway/media/i420_video_renderer.hpp"

namespace skyway {
namespace media {

/// @brief 映像の出力時の設定
struct V4l2VideoRendererOptions {
    /// @brief 出力時の横幅(px)を指定します。
    int scaled_width;
    /// @brief 出力時の高さ(px)を指定します。
    int scaled_height;
};

/// @brief 映像の描画を行うクラス
class V4l2VideoRenderer : public I420VideoRenderer, I420VideoRenderer::Listener {
public:
    /// @brief コンストラクタ
    /// @param video_out_path 映像出力デバイスの絶対パス
    /// @param options 映像の出力時の設定
    V4l2VideoRenderer(const std::string& video_out_path, const V4l2VideoRendererOptions& options);
    ~V4l2VideoRenderer();

    // I420VideoRenderer::Listerner
    void OnFrame(const uint8_t* y, const uint8_t* u, const uint8_t* v, int width, int height);

private:
    const std::string video_out_path_;
    int v4l2_file_descriptor_ = -1;
};

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_V4L2_VIDEO_RENDERER_HPP_ */
