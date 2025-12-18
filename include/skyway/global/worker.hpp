//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
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
    
    /// @brief コンストラクタ
    ///
    /// @details
    /// デバッグのためにWorker内部で管理しているスレッドに名前をつけることができます。
    /// なお、PFはAndroid, iOS, Linuxのみ対応しています。
    ///
    /// @param name
    /// スレッドの名前
    /// 全てのPFをサポートするために16文字以下でなければいけません。
    Worker(const std::string& name);
    /// @brief デストラクタ
    ///
    /// @details
    /// WorkerスレッドがJoinされます。
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
/// @endcond

}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_WORKER_HPP_ */
