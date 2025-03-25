#ifndef ORIGAMI_EVENTS_MOUSE_EVENT_HPP
#define ORIGAMI_EVENTS_MOUSE_EVENT_HPP

#include <origami/events/event.hpp>

namespace origami {
class MouseEvent : public Event {
protected:
  MouseEvent();

public:
  int GetCategoryFlags() const override;
  // TODO: should we move x and y floats to here
};

class MouseMove : public MouseEvent {
public:
  MouseMove(float x_, float y_);
  EventType GetType() const override;
  float x, y;
};

class MouseScroll : public MouseEvent {
public:
  MouseScroll(float x_, float y_);
  EventType GetType() const override;
  float x, y;
};

class MouseButtonEvent : public Event {
protected:
  MouseButtonEvent(int button_);

public:
  int GetCategoryFlags() const override;
  int button;
};

class MouseButtonPress : public MouseButtonEvent {
public:
  MouseButtonPress(int button);
  EventType GetType() const override;
};

class MouseButtonRelease : public MouseButtonEvent {
public:
  MouseButtonRelease(int button);
  EventType GetType() const override;
};
}

#endif
