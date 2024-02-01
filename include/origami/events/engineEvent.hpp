#ifndef ORIGAMI_EVENTS_ENGINE_EVENT_HPP
#define ORIGAMI_EVENTS_ENGINE_EVENT_HPP

#include <origami/events/event.hpp>

namespace origami {
class EngineEvent : public Event {
protected:
  EngineEvent();

public:
  int GetCategoryFlags() const override;
};
// An event called once, as soon as possible (ie when the event system is online)
class EngineInit : public EngineEvent {
  // TODO: add system and engine info
public:
  EngineInit();
  EventType GetType() const override;
};
// An event called when the engine is fully ready to start running an application
class EnginePrime : public EngineEvent {
public:
  EnginePrime();
  EventType GetType() const override;
};
// An event fired when the engine is doing goodbye
class EngineShutdown : public EngineEvent {
public:
  EngineShutdown();
  EventType GetType() const override;
};
}
#endif
