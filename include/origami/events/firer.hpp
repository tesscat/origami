#ifndef ORIGAMI_EVENTS_FIRER_HPP
#define ORIGAMI_EVENTS_FIRER_HPP

#include "origami/events/event.hpp"
#include <vector>
#include <functional>
#include <origami/events/engineEvent.hpp>
#include <origami/events/appEvent.hpp>
#include <origami/events/keyEvent.hpp>
#include <origami/events/mouseEvent.hpp>
#include <origami/events/windowEvent.hpp>

namespace origami {
template<Eventable T>
class EventFirer {
public:
  void Fire(T& event) { // TODO: unduplicate, make threaded
    for (std::function<void(T&)> handler : handlers) {
      handler(event);
      if (event.handled) {
        break;
      }
    }
  }
  std::vector<std::function<void(T&)>> handlers;
  void Add(std::function<void(T&)> fn) {
    handlers.push_back(fn);
  }
};

#define FIRE(class_, name) \
private: \
  EventFirer<class_> name; \
public: \
  inline void Add(std::function<void(class_&)> fn) { \
    name.handlers.push_back(fn); \
  } \
  inline void Fire(class_& event) { \
    name.Fire(event); \
  }
  

class EventHandler {
  // EventFirer<EngineInit> engineInitFirer;
  // void add(std::function<void(EngineInit&)> fn) {
  //   engineInitFirer.handlers.push_back(fn);
  // }
  // void fire(EngineInit& event) {
  //   engineInitFirer.Fire(event);
  // }
  FIRE(EngineInit, engineInitFirer) // TODO: come up with a better name
  FIRE(EnginePrime, enginePrimeFirer) // scheme bevause this sucks
  FIRE(EngineShutdown, engineShutdownFirer)
  FIRE(AppHeartbeat, appHeartbeatFirer)
  FIRE(AppRender, appRenderFirer)
  FIRE(WindowClose, windowCloseFirer)
  FIRE(WindowResize, windowResizeFirer)
  FIRE(WindowMove, windowMoveFirer)
  FIRE(WindowFocus, windowFocusFirer)
  FIRE(WindowLostFocus, windowLostFocusFirer)
  FIRE(KeyPress, keyPressFirer)
  FIRE(KeyRelease, keyReleaseFirer)
  FIRE(MouseButtonPress, mouseButtonPressFirer)
  FIRE(MouseButtonRelease, mouseButtonReleaseFirer)
  FIRE(MouseMove, mouseMoveFirer)
  FIRE(MouseScroll, mouseScrollFirer)

private:
  std::vector<std::function<void(Event&)>> engineEvents;
  std::vector<std::function<void(Event&)>> appEvents;
  std::vector<std::function<void(Event&)>> windowEvents;
  std::vector<std::function<void(Event&)>> inputEvents;
  std::vector<std::function<void(Event&)>> keyboardEvents;
  std::vector<std::function<void(Event&)>> mouseEvents;
  std::vector<std::function<void(Event&)>> mouseButtonEvents;

  // TODO: make threaded
  void FireContinuous(Event& event, std::vector<std::function<void(Event&)>>& handlers);
public:
  void RegisterCategoryHandler(const int categories,
                               const std::function<void(Event &)> fn);

  void FireCategory(Event& event);
};


} // namespace origami
#endif
