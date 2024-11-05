//
//  i420_video_renderer.hpp
//  skyway
//
//  Created by ogura on 2024/4/2.
//  Copyright © 2024 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_MEDIA_I420_VIDEO_RENDERER_HPP_
#define SKYWAY_MEDIA_I420_VIDEO_RENDERER_HPP_

#include <mutex>

#include <api/media_stream_interface.h>

#include "skyway/core/stream/remote/video_stream.hpp"

namespace skyway {
namespace media {

/// @brief 映像の出力時の設定
struct I420VideoRendererOptions {
    /// @brief 出力時の横幅(px)を指定します。
    boost::optional<int> scaled_width;
    /// @brief 出力時の高さ(px)を指定します。
    boost::optional<int> scaled_height;
};

/// @brief SubscribeしたVideoStreamの映像を取得するクラス
class I420VideoRenderer : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
public:
    /// @brief RemoteVideoStreamにて映像フレームが更新された際に呼ばれるイベントリスナー
    class Listener {
    public:
        /// @brief 映像フレームの更新時に発火するイベント
        /// @param y 更新された映像のY成分
        /// @param u 更新された映像のU成分
        /// @param v 更新された映像のV成分
        /// @param width 映像の横幅
        /// @param height 映像の縦幅
        virtual void OnFrame(
            const uint8_t* y, const uint8_t* u, const uint8_t* v, int width, int height) = 0;
    };

    /// @brief コンストラクタ
    /// @param options 取得する映像フレームの設定
    I420VideoRenderer(const I420VideoRendererOptions& options);
    ~I420VideoRenderer();

    /// @brief I420VideoRenderer::Listenerを登録します。
    /// @param listener 映像の更新があった際に呼ばれるイベントリスナー
    void RegisterListener(Listener* listener);

    /// @brief イベントリスナーの登録を解除します。
    void UnregisterListener();

    /// @brief RemoteVideoStreamをRendererに登録します。
    /// @param stream SubscribeしたRemoteVideoStream
    void Render(std::shared_ptr<core::stream::remote::RemoteVideoStream> stream);

    // rtc::VideoSinkInterface<webrtc::VideoFrame>
    void OnFrame(const webrtc::VideoFrame& frame) override;

private:
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track_;
    std::mutex rendering_mtx_;
    const I420VideoRendererOptions options_;
    Listener* listener_ = nullptr;
};

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_I420_VIDEO_RENDERER_HPP_ */
