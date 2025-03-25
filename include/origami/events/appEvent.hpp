#ifndef ORIGAMI_EVENTS_APP_EVENT_HPP
#define ORIGAMI_EVENTS_APP_EVENT_HPP

#include <origami/events/event.hpp>

namespace origami {

class AppEvent : public Event {
protected:
  AppEvent(float delta_);

public:
  int GetCategoryFlags() const override;

  // Time since last fired
  float delta;
};

// Fires at a regular interval
class AppHeartbeat : public AppEvent{
public:
  AppHeartbeat(float delta);

  EventType GetType() const override;
};
// Fires whenever a frame is rendered 
class AppRender : public AppEvent{
public:
  AppRender(float delta);

  EventType GetType() const override;
};
}

#endif
