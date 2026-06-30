//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_MEDIA_STREAM_ABSTRACT_STREAM_BASE_HPP_
#define SKYWAY_MEDIA_STREAM_ABSTRACT_STREAM_BASE_HPP_

#include <memory>
#include <string>

#include "skyway/domain/core_convert_helper.hpp"

namespace skyway {
namespace media {
namespace stream {
namespace abstract {

template <typename InterfaceT, typename CoreInterfaceT, typename CoreT>
class StreamBase : public InterfaceT {
public:
    /// @copydoc skyway::media::stream::interface::Stream::Id
    std::string Id() override { return core_->Id(); }

    /// @copydoc skyway::media::stream::interface::Stream::Side
    domain::Side Side() override {
        return domain::core_convert_helper::ConvertToPlatformSide(core_->Side());
    }

    /// @copydoc skyway::media::stream::interface::Stream::ContentType
    domain::ContentType ContentType() override {
        return domain::core_convert_helper::ConvertToPlatformContentType(core_->ContentType());
    }

    /// @cond INTERNAL_SECTION
    std::shared_ptr<CoreInterfaceT> GetCore() override { return core_; }
    /// @endcond

protected:
    /// @cond INTERNAL_SECTION
    explicit StreamBase(std::shared_ptr<CoreT> core) : core_(core) {}
    std::shared_ptr<CoreT> core_;
    /// @endcond
};

}  // namespace abstract
}  // namespace stream
}  // namespace media
}  // namespace skyway

#endif  // SKYWAY_MEDIA_STREAM_ABSTRACT_STREAM_BASE_HPP_
