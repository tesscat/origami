#include <origami/events/appEvent.hpp>

namespace origami {
AppEvent::AppEvent(float delta_) : delta{delta_} {}
int AppEvent::GetCategoryFlags() const { return EventCategory::App; }

AppHeartbeat::AppHeartbeat(float delta) : AppEvent{delta} {}
EventType AppHeartbeat::GetType() const { return EventType::AppHeartbeat; }

AppRender::AppRender(float delta) : AppEvent{delta} {}
EventType AppRender::GetType() const { return EventType::AppRender; }
} // namespace origami
