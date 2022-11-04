#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "export.hh"

struct Scheduler
{
	using Task = std::function<void (double)>;
	
	[[nodiscard]] COMMONSAPI int32_t scheduleTask(long msDelay, Task task);
	COMMONSAPI void cancelTask(int32_t id);
	COMMONSAPI void rescheduleTask(int32_t id, long msAlteration);
	COMMONSAPI void update(double impulse);
	std::vector<std::pair<std::chrono::steady_clock::time_point, Task>> tasks;
};
