#include <origami/events/event.hpp>

namespace origami {
bool Event::IsInCategory(EventCategory category) {
  return GetCategoryFlags() & category;
}
}
