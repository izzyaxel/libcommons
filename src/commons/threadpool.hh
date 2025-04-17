#pragma once

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <thread>
#include <functional>
#include <queue>

struct ThreadPool
{
  explicit ThreadPool(size_t poolSize = std::max(std::thread::hardware_concurrency() - 1u, 1u));

  ~ThreadPool();
  
  template <typename F, typename... Args> auto enqueue(F func, Args... args)
  {
    auto invokeBinding = std::bind(std::forward<F>(std::move(func)), std::forward<Args>(args)...);
    using invokePkg = std::packaged_task<std::invoke_result_t<decltype(invokeBinding)>()>;
    invokePkg pkg{std::move(invokeBinding)};
    auto future = pkg.get_future();
    this->queueMutex.lock();
    this->taskQueue.push(std::make_unique<Task<invokePkg>>(std::move(pkg)));
    this->queueMutex.unlock();
    this->queueCV.notify_one();
    return future;
  }

private:
  std::atomic_bool runSem{true};
  std::condition_variable queueCV;
  std::mutex queueMutex, cvMutex;
  std::vector<std::thread> threads;

  struct TaskBase
  {
    virtual ~TaskBase() = default;
    virtual void execute() = 0;
  };

  template <typename P> struct Task final : TaskBase
  {
    explicit Task(P&& pkg) : pkg{std::forward<P&&>(pkg)}
    {}
    
    void execute() override
    {
      pkg();
    }
    
    P pkg;
  };

  std::queue<std::unique_ptr<TaskBase>> taskQueue;

  void threadRun();
};
