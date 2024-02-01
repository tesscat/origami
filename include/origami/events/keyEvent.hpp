#ifndef TM_EVENTS_KEY_EVENT_HPP
#define TM_EVENTS_KEY_EVENT_HPP

// #include <origami/graphics/window.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <origami/events/event.hpp>

template<typename T>
class Event;

namespace origami {
class KeyEvent : public Event {
protected:
  KeyEvent(int keyCode, GLFWwindow* window);

public:
  int GetCategoryFlags() const override;

  std::string GetKeyName();

  int keyCode;

  GLFWwindow* window;
};

class KeyPress : public KeyEvent {
public:
  KeyPress(int keyCode, GLFWwindow* window);

  EventType GetType() const override;
};

class KeyRelease : public KeyEvent {
public:
  KeyRelease(int keyCode, GLFWwindow* window);

  EventType GetType() const override;
};
}

#endif
