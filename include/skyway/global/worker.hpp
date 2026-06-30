//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_GLOBAL_WORKER_HPP_
#define SKYWAY_GLOBAL_WORKER_HPP_

#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

#include "skyway/global/interface/worker.hpp"

namespace skyway {
namespace global {

class Worker : public interface::Worker {
public:
    using Task = std::function<void()>;

    Worker(const std::string& name);

    ~Worker();

    void AddTask(Task& task) override;
    void AddTask(const Task&& task) override;
    void Join() override;

private:
    void ProcessWorker(const std::string& name);
    int SetThreadName(const std::string& name);
    std::deque<Task> tasks_;
    std::mutex mtx_;
    std::condition_variable cv_;
    bool is_termination_requested_ = false;
    std::thread worker_;
};

}  // namespace global
}  // namespace skyway

#endif
