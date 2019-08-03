#pragma once

#include <chrono>
#include <vector>
#include <functional>

struct Scheduler
{
	using Task = std::function<void (double)>;
	
	[[nodiscard]] int32_t scheduleTask(long msDelay, Task task);
	void cancelTask(int32_t id);
	void rescheduleTask(int32_t id, long msAlteration);
	void update(double impulse);
	std::vector<std::pair<std::chrono::steady_clock::time_point, Task>> tasks;
};
