//
//  worker.hpp
//  skyway
//
//  Created by Naoto Takahashi on 2024/03/05.
//  Copyright © 2024 NTT Communications. All rights reserved.
//

#ifndef SKYWAY_GLOBAL_WORKER_HPP_
#define SKYWAY_GLOBAL_WORKER_HPP_

#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "skyway/global/interface/worker.hpp"

namespace skyway {
namespace global {

/// @cond INTERNAL_SECTION
class Worker : public interface::Worker {
public:
    using Task = std::function<void()>;

    Worker();
    /// @brief デストラクタ
    ///
    /// @details
    /// WorkerスレッドがJoinされます。
    ~Worker();

    void AddTask(Task& task) override;
    void AddTask(const Task&& task) override;
    void Join() override;

private:
    void ProcessWorker();
    std::deque<Task> tasks_;
    std::mutex mtx_;
    std::condition_variable cv_;
    bool is_termination_requested_ = false;
    std::thread worker_;
};
/// @endcond

}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_WORKER_HPP_ */
