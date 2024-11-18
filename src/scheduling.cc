#include "commons/scheduling.hh"

int32_t Scheduler::scheduleTask(const long msDelay, const Task& taskCallback)
{
  std::chrono::steady_clock::time_point future = std::chrono::steady_clock::now() + std::chrono::steady_clock::duration{std::chrono::milliseconds(msDelay)};
  const int32_t id = (int32_t)this->tasks.size();
  this->tasks[id] = std::pair{future, taskCallback};
  return id;
}

void Scheduler::cancelTask(const int32_t id)
{
  this->tasks.erase(this->tasks.begin() + id);
}

void Scheduler::rescheduleTask(const int32_t id, const long msAlteration)
{
  this->tasks[id].first += std::chrono::steady_clock::duration{msAlteration};
}

void Scheduler::update(const double impulse)
{
  if(!this->tasks.empty())
  {
    for(uint32_t i = 0; i < this->tasks.size(); i++)
    {
      const auto& tList = this->tasks[i];
      if(std::chrono::steady_clock::now() >= tList.first)
      {
        tList.second(impulse);
        this->tasks.erase(this->tasks.begin() + i);
      }
    }
  }
}
