//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_GLOBAL_INTERFACE_WORKER_HPP_
#define SKYWAY_GLOBAL_INTERFACE_WORKER_HPP_

#include <functional>

namespace skyway {
namespace global {
namespace interface {

/// @cond INTERNAL_SECTION
/// @brief シングルスレッドで動くWorker
///
/// @details
///  新たにWorkerスレッドを作成し、`AddTask`によってタスクがキューで管理され、実行されます。
class Worker {
public:
    using Task        = std::function<void()>;
    virtual ~Worker() = default;
    /// @brief タスクの追加
    ///
    /// @details
    /// 追加され次第、Workerスレッドが処理を開始します。
    /// すでに追加されたタスクが完了していない場合、完了後に処理を開始します。
    /// タスクにおいてリファレンスキャプチャをしている場合、キャプチャしているオブジェクトよりもWorkerオブジェクトを先に破棄してください。
    /// - Parameter task: タスク
    virtual void AddTask(Task& task) = 0;

    /// @brief タスクの追加
    ///
    /// @details
    /// 追加され次第、Workerスレッドが処理を開始します。
    /// すでに追加されたタスクが完了していない場合、完了後に処理を開始します。
    /// タスクにおいてリファレンスキャプチャをしている場合、キャプチャしているオブジェクトよりもWorkerオブジェクトを先に破棄してください。
    /// - Parameter task: タスク
    virtual void AddTask(const Task&& task) = 0;

    /// @brief Workerスレッドの完了を待機し、スレッドをJoinします。
    ///
    /// @details このAPIは明示的なもので、`Join()`をコールせずThread
    /// Poolを破棄しても問題ありません。また、何度もコールすることができます。
    virtual void Join() = 0;
};
/// @endcond

}  // namespace interface
}  // namespace global
}  // namespace skyway

#endif /* SKYWAY_GLOBAL_INTERFACE_WORKER_HPP_ */
