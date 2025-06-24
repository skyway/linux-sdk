//
//  opencv_capturer_video_source.hpp
//  skyway
//
//  Created by ogura on 2024/12/11.
//  Copyright © 2024 NTT DOCOMO BUSINESS, Inc. All rights reserved.
//

// Define “SKYWAY_ENABLE_OPENCV” if you want to use OpenCV functionality
#ifdef SKYWAY_ENABLE_OPENCV

#ifndef SKYWAY_MEDIA_OPENCV_CAPTURER_VIDEO_SOURCE_HPP_
#define SKYWAY_MEDIA_OPENCV_CAPTURER_VIDEO_SOURCE_HPP_

#include "skyway/media/i420_capturer_video_source.hpp"

#include <api/media_stream_interface.h>
#include <opencv2/opencv.hpp>

namespace skyway {
namespace media {
namespace opencv {

/// @brief OpenCVを利用した描画処理を行うクラス
/// @details 利用する際には、SKYWAY_ENABLE_OPENCVマクロを定義してください。
class OpenCVCapturerVideoSource : public interface::CapturerVideoSource {
public:
    /// @cond INTERNAL_SECTION
    class OpenCVInternalCapturerVideoSource
        : public I420CapturerVideoSource::I420InternalCapturerVideoSource {
    public:
        ~OpenCVInternalCapturerVideoSource();

        static rtc::scoped_refptr<OpenCVInternalCapturerVideoSource> Create();

        bool Render(cv::Mat mat);

    protected:
        OpenCVInternalCapturerVideoSource();
    };
    /// @endcond
    OpenCVCapturerVideoSource();
    ~OpenCVCapturerVideoSource();

    /// @brief cv::Matで作成した画像を描画、送信します。
    void Render(cv::Mat mat);

    /// @cond INTERNAL_SECTION
    // Impl interface::InternalCapturerVideoSource
    rtc::scoped_refptr<interface::InternalCapturerVideoSource> GetSource();
    /// @endcond

private:
    rtc::scoped_refptr<OpenCVInternalCapturerVideoSource> source_;
};

}  // namespace opencv
}  // namespace media
}  // namespace skyway

#endif /* SKYWAY_MEDIA_OPENCV_CAPTURER_VIDEO_SOURCE_HPP_ */
#endif /* SKYWAY_ENABLE_OPENCV */
