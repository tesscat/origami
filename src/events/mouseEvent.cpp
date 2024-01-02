#include <origami/events/mouseEvent.hpp>

namespace origami {
MouseEvent::MouseEvent() {}
int MouseEvent::GetCategoryFlags() const { return EventCategory::Mouse | EventCategory::Input; }

MouseMove::MouseMove(float x_, float y_) : x{x_}, y{y_} {}
EventType MouseMove::GetType() const { return EventType::MouseMove; }

MouseScroll::MouseScroll(float x_, float y_) : x{x_}, y{y_} {}
EventType MouseScroll::GetType() const { return EventType::MouseScroll; }

MouseButtonEvent::MouseButtonEvent(int button_) : button{button_} {}
int MouseButtonEvent::GetCategoryFlags() const {
  return EventCategory::Mouse | EventCategory::MouseButton |
         EventCategory::Input;
}

MouseButtonPress::MouseButtonPress(int button) : MouseButtonEvent{button} {}
EventType MouseButtonPress::GetType() const {
  return EventType::MouseButtonPress;
}

MouseButtonRelease::MouseButtonRelease(int button) : MouseButtonEvent{button} {}
EventType MouseButtonRelease::GetType() const {
  return EventType::MouseButtonRelease;
}
} // namespace origami
