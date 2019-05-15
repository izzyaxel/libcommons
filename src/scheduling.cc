#include "commons/scheduling.hh"

int32_t Scheduler::scheduleTask(long msDelay, Task taskCallback)
{
	std::chrono::steady_clock::time_point future = std::chrono::steady_clock::now() + std::chrono::steady_clock::duration{std::chrono::milliseconds(msDelay)};
	int32_t id = static_cast<int >(this->tasks.size());
	this->tasks[id] = std::pair<std::chrono::steady_clock::time_point, Task>{future, taskCallback};
	return id;
}

void Scheduler::cancelTask(int32_t id)
{
	this->tasks.erase(this->tasks.begin() + id);
}

void Scheduler::rescheduleTask(int32_t id, long msAlteration)
{
	this->tasks[id].first += std::chrono::steady_clock::duration{msAlteration};
}

void Scheduler::update(double impulse)
{
	if(!this->tasks.empty())
	{
		for(uint32_t i = 0; i < this->tasks.size(); i++)
		{
			auto const &tList = this->tasks[i];
			if(std::chrono::steady_clock::now() >= tList.first)
			{
				tList.second(impulse);
				this->tasks.erase(this->tasks.begin() + i);
			}
		}
	}
}
