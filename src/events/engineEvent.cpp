#include <origami/events/engineEvent.hpp>

namespace origami {
EngineEvent::EngineEvent() {}
int EngineEvent::GetCategoryFlags() const { return EventCategory::Engine; }

EngineInit::EngineInit() {}
EventType EngineInit::GetType() const { return EventType::EngineInit; }

EnginePrime::EnginePrime() {}
EventType EnginePrime::GetType() const { return EventType::EnginePrime; }

EngineShutdown::EngineShutdown() {}
EventType EngineShutdown::GetType() const { return EventType::EngineShutdown; }
} // namespace origami
