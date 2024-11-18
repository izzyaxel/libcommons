#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "export.hh"

struct Scheduler
{
  using Task = std::function<void (double)>;

  [[nodiscard]] COMMONS_API int32_t scheduleTask(long msDelay, const Task& taskCallback);

  COMMONS_API void cancelTask(int32_t id);

  COMMONS_API void rescheduleTask(int32_t id, long msAlteration);

  COMMONS_API void update(double impulse);

  std::vector<std::pair<std::chrono::steady_clock::time_point, Task>> tasks;
};
