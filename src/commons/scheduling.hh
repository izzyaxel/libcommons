#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "export.hh"

struct Scheduler
{
	using Task = std::function<void (double)>;
	
	[[nodiscard]] EXPORT int32_t scheduleTask(long msDelay, Task task);
	EXPORT void cancelTask(int32_t id);
	EXPORT void rescheduleTask(int32_t id, long msAlteration);
	EXPORT void update(double impulse);
	std::vector<std::pair<std::chrono::steady_clock::time_point, Task>> tasks;
};
