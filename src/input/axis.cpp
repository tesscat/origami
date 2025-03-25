#include <GLFW/glfw3.h>
#include <origami/input/axis.hpp>

namespace origami::input {
Axis::~Axis() {}

KeyAxis::KeyAxis(int keycode_positive_, int keycode_negative_, graphics::Window* handle) : keycode_positive{keycode_positive_}, keycode_negative{keycode_negative_}, window_handle{handle} {}
float KeyAxis::Value(int _dimension) {
  float value = 0.0f;
  if (glfwGetKey(window_handle->handle, keycode_positive) == GLFW_PRESS)
    value += 1.0f;
  if (glfwGetKey(window_handle->handle, keycode_negative) == GLFW_PRESS)
    value -= 1.0f;

  return value;
}

KeyAxis::~KeyAxis() {}

MouseAxis::MouseAxis(graphics::Window* handle_) : handle{handle_} {}
float MouseAxis::Value(int dimension) {
  if (dimension == 0) {
    return handle->lastX - handle->mouseX;
  } else if (dimension == 1) {
    return handle->lastY - handle->mouseY;
  } else {return 0;}
}

MouseAxis::~MouseAxis() {}
}
