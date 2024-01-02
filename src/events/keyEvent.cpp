#include <origami/events/keyEvent.hpp>
#include <GLFW/glfw3.h>

namespace origami {
KeyEvent::KeyEvent(int keyCode_, GLFWwindow* window_) : keyCode{keyCode_}, window{window_} {};
int KeyEvent::GetCategoryFlags() const { return EventCategory::Keyboard | EventCategory::Input; }
std::string KeyEvent::GetKeyName() { // TODO: optimise
  const char* name = glfwGetKeyName(GLFW_KEY_UNKNOWN, keyCode);
  if (name == NULL) {
    return std::string();
  }
  return std::string { name };
}

KeyPress::KeyPress(int keyCode, GLFWwindow* window)
    : KeyEvent{keyCode, window} {}
EventType KeyPress::GetType() const { return EventType::KeyPress; }

KeyRelease::KeyRelease(int keyCode, GLFWwindow* window) : KeyEvent{keyCode, window} {}
EventType KeyRelease::GetType() const { return EventType::KeyRelease; }
} // namespace origami
