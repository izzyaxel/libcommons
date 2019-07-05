#pragma once

#include <functional>
#include <tuple>

/// Usage:
/// template <typename ...Args> struct EventBase : public std::function<void(Args ...)>
/// {
///     using std::function<void(Args ...)>::function;
/// };
/// 
/// struct EventA : public EventBase<int>
/// {
///     using EventBase::EventBase;
/// };
/// 
/// struct EventB : public EventBase<int>
/// {
///     using EventBase::EventBase;
/// };
/// 
/// EventBus<EventA, EventB> eventBus;
/// 
/// The way this is set up allows multiple events with the same parameters to be treated as separate events
template <typename ... Ts> struct EventBus
{
	template <typename Event> void registerEventHandler(Event const &event)
	{
		std::get<std::vector<Event>>(this->registrars).push_back(event);
	}
	
	template <typename Event, typename ... Args> void post(Args ... args)
	{
		for(auto const &event : std::get<std::vector<Event>>(this->registrars)) event(args ...);
	}

private:
	std::tuple<std::vector<Ts> ...> registrars;
};
