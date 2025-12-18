//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_I420_VIDEO_RENDERER_HPP_
#define SKYWAY_MEDIA_I420_VIDEO_RENDERER_HPP_

#include <mutex>
#include <optional>

#include "skyway/media/interface/i420_video_renderer.hpp"

namespace skyway {
namespace media {
/// @brief SubscribeしたVideoStreamの映像を取得するクラス
class I420VideoRenderer : public interface::I420VideoRenderer {
public:
    /// @brief コンストラクタ
    /// @param options 取得する映像フレームの設定
    I420VideoRenderer(const interface::I420VideoRendererOptions& options);
    ~I420VideoRenderer();

    /// @brief I420VideoRenderer::Listenerを登録します。
    /// @param listener 映像の更新があった際に呼ばれるイベントリスナー
    void RegisterListener(interface::I420VideoRenderer::Listener* listener) override;

    /// @brief イベントリスナーの登録を解除します。
    void UnregisterListener(interface::I420VideoRenderer::Listener* listener) override;

    /// @brief RemoteVideoStreamをRendererに登録します。
    /// @param stream SubscribeしたRemoteVideoStream
    void Render(std::shared_ptr<core::stream::remote::RemoteVideoStream> stream) override;

    // rtc::VideoSinkInterface<webrtc::VideoFrame>
    void OnFrame(const webrtc::VideoFrame& frame) override;

protected:
    std::optional<interface::I420Frame> ConvertI420Frame(const webrtc::VideoFrame& frame);

private:
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track_;
    std::mutex rendering_mtx_;
    const interface::I420VideoRendererOptions options_;
    std::unordered_set<Listener*> listeners_;
};

}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_I420_VIDEO_RENDERER_HPP_ */
