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
template <typename... Ts> struct EventBus
{
  /// Register an event handler
  /// \tparam Event The type of event to register
  /// \param event The event callback and data
  template <typename Event> void registerEventHandler(Event const &event)
  {
    std::get<std::vector<Event>>(this->registrars).push_back(event);
  }

  /// Activate a given event's handlers
  /// \tparam Event The type of event to post
  /// \tparam Args The type of the arguments
  /// \param args The arguments to pass into the callbacks that handle this event type
  template <typename Event, typename... Args> void post(Args... args)
  {
    for(auto const &event : std::get<std::vector<Event>>(this->registrars)) event(args...);
  }

private:
  std::tuple<std::vector<Ts>...> registrars;
};
