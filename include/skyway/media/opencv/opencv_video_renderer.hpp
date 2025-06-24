//
//  opencv_video_renderer.hpp
//  skyway
//
//  Created by ogura on 2024/12/11.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

// Define “SKYWAY_ENABLE_OPENCV” if you want to use OpenCV functionality
#ifdef SKYWAY_ENABLE_OPENCV

#ifndef SKYWAY_MEDIA_OPENCV_VIDEO_RENDERER_HPP_
#define SKYWAY_MEDIA_OPENCV_VIDEO_RENDERER_HPP_

#include "skyway/media/i420_video_renderer.hpp"

#include <thread>
#include <unordered_set>

#include <memory>

#include <opencv2/opencv.hpp>

namespace skyway {
namespace media {
namespace opencv {

/// @brief 映像の描画を行うクラス
/// @details 利用する際には、SKYWAY_ENABLE_OPENCVマクロを定義してください。
class OpenCVVideoRenderer : public I420VideoRenderer {
public:
    class Listener {
    public:
        virtual ~Listener()               = default;
        virtual void OnFrame(cv::Mat mat) = 0;
    };

    /// @brief コンストラクタ
    OpenCVVideoRenderer();
    ~OpenCVVideoRenderer();

    /// @brief リスナーを登録します
    /// @param listener 登録するリスナー
    void RegisterListener(Listener* listener);
    /// @brief 登録しているリスナーを解除します
    /// @param listener 登録を解除するリスナー
    void UnregisterListener(Listener* listener);

    // Impl I420VideoRenderer
    void OnFrame(const webrtc::VideoFrame& frame) override;

private:
    cv::Mat I420ToMat(const interface::I420Frame& frame);
    std::mutex listeners_mtx_;
    std::unordered_set<Listener*> listeners_;
};
}  // namespace opencv
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_V4L2_VIDEO_RENDERER_HPP_ */
#endif /* SKYWAY_ENABLE_OPENCV */
