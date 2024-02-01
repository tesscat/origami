#ifndef ORIGAMI_EVENTS_WINDOW_EVENT_HPP
#define ORIGAMI_EVENTS_WINDOW_EVENT_HPP

#include <origami/events/event.hpp>

namespace origami {
class WindowEvent : public Event {
  // TODO: add a window pointer!
protected:
  WindowEvent();
public:
  int GetCategoryFlags() const override;
};

class WindowClose : public WindowEvent {
public:
  WindowClose();
  EventType GetType() const override;
};

class WindowResize : public WindowEvent {
public:
  WindowResize(int width_, int height_);
  EventType GetType() const override;

  // The new values
  int width, height; // TODO: do we need old values
};

class WindowMove : public WindowEvent {
public:
  WindowMove(int x_, int y_);
  EventType GetType() const override;

  int x, y;
};

class WindowFocus : public WindowEvent {
public:
  WindowFocus();
  EventType GetType() const override;
};

class WindowLostFocus : public WindowEvent {
public:
  WindowLostFocus();
  EventType GetType() const override;
};
}

#endif
