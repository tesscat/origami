#include <origami/events/windowEvent.hpp>

namespace origami {
WindowEvent::WindowEvent() {}
int WindowEvent::GetCategoryFlags() const { return EventCategory::Window; }

WindowClose::WindowClose() {}
EventType WindowClose::GetType() const { return EventType::WindowClose; }

WindowResize::WindowResize(int width_, int height_)
    : width{width_}, height{height_} {}
EventType WindowResize::GetType() const { return EventType::WindowResize; }

WindowMove::WindowMove(int x_, int y_) : x{x_}, y{y_} {}
EventType WindowMove::GetType() const { return EventType::WindowMove; }

WindowFocus::WindowFocus() {}
EventType WindowFocus::GetType() const { return EventType::WindowFocus; }

WindowLostFocus::WindowLostFocus() {}
EventType WindowLostFocus::GetType() const {
  return EventType::WindowLostFocus;
}
} // namespace origami
