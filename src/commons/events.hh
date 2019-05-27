#pragma once

#include <unordered_map>
#include <vector>
#include <functional>

using EventID = int64_t;
using Callback = std::function<void()>;

struct EventBus
{
	/// Post an event, and run all callbacks associated with it
	/// \param id EventID of the event to post
	void post(EventID id);
	
	/// Register a callback to run when an event is posted
	/// \param id EventID of the event to register to
	/// \param callback The Callback to run when the event is posted
	void registerEventHandler(EventID id, Callback const &callback);
	
private:
	std::unordered_map<EventID, std::vector<Callback>> events;
};
