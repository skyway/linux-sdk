//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_CORE_INTERFACE_STREAM_HPP_
#define SKYWAY_CORE_INTERFACE_STREAM_HPP_

#include "skyway/model/domain.hpp"

namespace skyway {
namespace core {
namespace interface {

class Stream {
public:
    virtual ~Stream() = default;
    Stream(const std::string& id, model::Side side, model::ContentType content_type);

    std::string Id() const;

    model::Side Side() const;

    model::ContentType ContentType() const;

    virtual bool Enable() = 0;

    virtual bool Disable() = 0;

private:
    std::string id_;
    model::Side side_;
    model::ContentType content_type_;
};

}  // namespace interface
}  // namespace core
}  // namespace skyway

#endif
