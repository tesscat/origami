#ifndef ORIGAMI_EVENTS_EVENT_HPP
#define ORIGAMI_EVENTS_EVENT_HPP

#include <functional>
#include <vector>

template<typename T>
concept Eventable = requires(T a) {
  { a.handled } -> std::convertible_to<bool>;
};

namespace origami {


template<Eventable T>
class EventFirer; // forward def required

enum class EventType {
  None = 0,
  EngineInit, EnginePrime, EngineShutdown,
  AppHeartbeat, AppRender,
  WindowClose, WindowResize, WindowMove, WindowFocus, WindowLostFocus,
  KeyPress, /*TODO: do we need KeyHeld */ KeyRelease,
  MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll,
};

enum EventCategory {
  None = 0,
  Engine = 0b1,
  App = 0b10,
  Window = 0b100,
  Input = 0b1000,
  Keyboard = 0b10000,
  Mouse = 0b100000,
  MouseButton = 0b1000000,
};



class Event {
public:
  bool handled = false;
  virtual EventType GetType()  const = 0; // TODO: do we should have this
  virtual int GetCategoryFlags() const = 0;

  bool IsInCategory(EventCategory category);
};

}

#endif
