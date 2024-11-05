//
//  stream.hpp
//  skyway
//
//  Created by sandabu on 2022/01/12.
//  Copyright © 2022 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_STREAM_HPP_
#define SKYWAY_CORE_INTERFACE_STREAM_HPP_

#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

/// @brief MediaStreamやDataStreamの基底クラス
class Stream {
public:
    virtual ~Stream() = default;
    Stream(const std::string& id, model::Side side, model::ContentType content_type);

    /// @brief Idを取得します
    std::string Id() const;

    /// @brief Side(LocalかRemoteか)を取得します。
    model::Side Side() const;

    /// @brief ContentType(VideoかAudioかDataか)を取得します。
    model::ContentType ContentType() const;

    /// @cond INTERNAL_SECTION
    /// @brief Media通信もしくはData通信を開始します。
    virtual bool Enable() = 0;
    /// @brief Media通信もしくはData通信を停止します。
    virtual bool Disable() = 0;
    /// @endcond

private:
    std::string id_;
    model::Side side_;
    model::ContentType content_type_;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_STREAM_HPP_ */
