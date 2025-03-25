#include <origami/events/firer.hpp>

namespace origami {
void EventHandler::FireContinuous(Event& event, std::vector<std::function<void(Event&)>>& handlers) {
    for (std::function<void(Event&)> handler : handlers) {
      handler(event);
      if (event.handled) {
        break;
      }
    }
  }
  void EventHandler::RegisterCategoryHandler(const int categories,
                                        const std::function<void(Event &)> fn) {
    // TODO: BUG: do we need a != 0
    if (categories & EventCategory::Engine) {
      engineEvents.push_back(fn);
    }
    if (categories & EventCategory::App) {
      appEvents.push_back(fn);
    }
    if (categories & EventCategory::Window) {
      windowEvents.push_back(fn);
    }
    if (categories & EventCategory::Input) {
      inputEvents.push_back(fn);
    }
    if (categories & EventCategory::Keyboard) {
      keyboardEvents.push_back(fn);
    }
    if (categories & EventCategory::Mouse) {
      mouseEvents.push_back(fn);
    }
    if (categories & EventCategory::MouseButton) {
      mouseButtonEvents.push_back(fn);
    }
  }
  void EventHandler::FireCategory(Event &event) {
    int categories = event.GetCategoryFlags();
    // TODO: BUG: do we need a != 0
    if (categories & EventCategory::Engine) {
      FireContinuous(event, engineEvents);
    }
    if (categories & EventCategory::App) {
      FireContinuous(event, appEvents);
    }
    if (categories & EventCategory::Window) {
      FireContinuous(event, windowEvents);
    }
    if (categories & EventCategory::Input) {
      FireContinuous(event, inputEvents);
    }
    if (categories & EventCategory::Keyboard) {
      FireContinuous(event, keyboardEvents);
    }
    if (categories & EventCategory::Mouse) {
      FireContinuous(event, mouseEvents);
    }
    if (categories & EventCategory::MouseButton) {
      FireContinuous(event, mouseButtonEvents);
    }
  }
} // namespace origami
