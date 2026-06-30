//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_GLOBAL_INTERFACE_WORKER_HPP_
#define SKYWAY_GLOBAL_INTERFACE_WORKER_HPP_

#include <functional>

namespace skyway {
namespace global {
namespace interface {

class Worker {
public:
    using Task        = std::function<void()>;
    virtual ~Worker() = default;

    virtual void AddTask(Task& task) = 0;

    virtual void AddTask(const Task&& task) = 0;

    virtual void Join() = 0;
};

}  // namespace interface
}  // namespace global
}  // namespace skyway

#endif
