#include "commons/threadpool.hh"

ThreadPool::ThreadPool(const size_t poolSize)
{
  for(size_t i = 0; i < poolSize; i++) this->threads.emplace_back(&ThreadPool::threadRun, this);
}

ThreadPool::~ThreadPool()
{
  this->runSem.store(false);
  this->queueCV.notify_all();
  for(std::thread &th : this->threads) if(th.joinable()) th.join();
}

void ThreadPool::threadRun()
{
  while(true)
  {
    std::unique_ptr<TaskBase> task = nullptr;
    {
      std::unique_lock lock(this->queueMutex);
      this->queueCV.wait(lock, [this]() -> bool
      {
        return !this->runSem.load() || !this->taskQueue.empty();
      });

      if(!this->runSem.load() && this->taskQueue.empty())
      {
        return;
      }

      task = std::move(this->taskQueue.front());
      this->taskQueue.pop();
    }

    if(task)
    {
      task->execute();
    }
  }
}
