//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_LOCAL_STREAM_HPP_
#define SKYWAY_CORE_INTERFACE_LOCAL_STREAM_HPP_

#include <atomic>

#include "skyway/core/interface/stream.hpp"

namespace skyway {
namespace core {
namespace interface {

/// @brief LocalPersonで扱うStream
class LocalStream : public Stream {
public:
    virtual ~LocalStream() = default;

    /// @cond INTERNAL_SECTION
    /// @brief Streamが公開(`Publish`)されているかを取得します。
    bool IsPublished() const;

    void SetIsPublished(bool is_published);
    /// @endcond

protected:
    LocalStream(model::ContentType content_type);

private:
    std::atomic<bool> is_published_ = false;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif /* SKYWAY_CORE_INTERFACE_LOCAL_STREAM_HPP_ */
