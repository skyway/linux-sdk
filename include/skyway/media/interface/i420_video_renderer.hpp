//
//  i420_video_renderer.hpp
//  skyway
//
//  Created by ogura on 2025/1/10.
//  Copyright © 2025 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

#ifndef SKYWAY_MEDIA_INTERFACE_I420_VIDEO_RENDERER_HPP_
#define SKYWAY_MEDIA_INTERFACE_I420_VIDEO_RENDERER_HPP_

#include <mutex>
#include <unordered_set>

#include "skyway/core/stream/remote/video_stream.hpp"
#include "skyway/media/interface/video_renderer.hpp"

namespace skyway {
namespace media {
namespace interface {

/// @brief 映像の出力時の設定
struct I420VideoRendererOptions {
    /// @brief 出力時の横幅(px)を指定します。
    std::optional<int> scaled_width;
    /// @brief 出力時の高さ(px)を指定します。
    std::optional<int> scaled_height;
};

/// @brief 映像フレーム
struct I420Frame {
    /// @brief 映像のY成分
    const uint8_t* y;
    /// @brief 映像のU成分
    const uint8_t* u;
    /// @brief 映像のV成分
    const uint8_t* v;
    /// @brief 映像のY成分のStride
    int stride_y;
    /// @brief 映像のY成分のStride
    int stride_u;
    /// @brief 映像のY成分のStride
    int stride_v;
    /// @brief width 映像の横幅
    int width;
    /// @brief height 映像の縦幅
    int height;

    /// @cond INTERNAL_SECTION
    rtc::scoped_refptr<webrtc::I420BufferInterface> i420_buffer;
    /// @endcond
};

/// @brief SubscribeしたVideoStreamの映像を取得するインターフェース
class I420VideoRenderer : public VideoRenderer {
public:
    /// @brief RemoteVideoStreamにて映像フレームが更新された際に呼ばれるイベントリスナー
    class Listener {
    public:
        virtual ~Listener()                   = default;
        virtual void OnFrame(I420Frame frame) = 0;
    };

    /// @brief I420VideoRenderer::Listenerを登録します。
    /// @param listener 映像の更新があった際に呼ばれるイベントリスナー
    virtual void RegisterListener(Listener* listener) = 0;

    /// @brief イベントリスナーの登録を解除します。
    virtual void UnregisterListener(Listener* listener) = 0;

    /// @brief RemoteVideoStreamをRendererに登録します。
    /// @param stream SubscribeしたRemoteVideoStream
    virtual void Render(std::shared_ptr<core::stream::remote::RemoteVideoStream> stream) = 0;

    // rtc::VideoSinkInterface<webrtc::VideoFrame>
    virtual void OnFrame(const webrtc::VideoFrame& frame) = 0;
};

}  // namespace interface
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_INTERFACE_I420_VIDEO_RENDERER_HPP_ */
