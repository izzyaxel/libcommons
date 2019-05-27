#include "commons/events.hh"

void EventBus::post(EventID id)
{
	if(!this->events[id].empty()) for(auto const &cb : this->events[id]) cb();
}

void EventBus::registerEventHandler(EventID id, Callback const &callback)
{
	this->events[id].push_back(callback);
}
