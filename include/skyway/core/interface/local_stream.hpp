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

class LocalStream : public Stream {
public:
    virtual ~LocalStream() = default;

    bool IsPublished() const;

    void SetIsPublished(bool is_published);

protected:
    LocalStream(model::ContentType content_type);

private:
    std::atomic<bool> is_published_ = false;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
