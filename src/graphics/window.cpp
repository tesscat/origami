#include "GLFW/glfw3.h"
#include "origami/events/mouseEvent.hpp"
#include "origami/log.hpp"
#include <origami/events/event.hpp>
#include <origami/graphics/window.hpp>
#include <config.hpp>

#include <iomanip>
#include <utility>

namespace origami::graphics {

void glfwErrorCallback(int i, const char* c) noexcept(false) {
  std::stringstream ss;
  ss << "Error #0x" << std::hex << i << ": " << c;
  throw GLFWErr(ss.str());
}

GLFWErr::GLFWErr(std::string err_) : err { err_ } {};
const char* GLFWErr::what() const noexcept {
  return err.c_str();
}

GraphicsCreateError::GraphicsCreateError(std::string err_) : err { err_ } {}
const char* GraphicsCreateError::what() const noexcept {
  return err.c_str();
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // TODO: optimise, this is a busy fn
  Window* wind = (Window*) glfwGetWindowUserPointer(window);
  if (action == GLFW_PRESS) {
    KeyPress keyPress { scancode, window };
    wind->eventHandler.Fire(keyPress);
    wind->eventHandler.FireCategory(keyPress);
  }
  else if (action == GLFW_RELEASE) {
    KeyRelease keyRelease = { scancode, window };
    wind->eventHandler.Fire(keyRelease);
    wind->eventHandler.FireCategory(keyRelease);
  }
}

void Window::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
  Window* wind = (Window*) glfwGetWindowUserPointer(window);
  float xoffset = xpos - wind->lastXEvent;
  float yoffset = ypos - wind->lastYEvent;
  wind->lastXEvent = xpos;
  wind->lastYEvent = ypos;

  wind->firstMouse = false;

  MouseMove mouseMove {xoffset, yoffset};
  wind->eventHandler.Fire(mouseMove);
  wind->eventHandler.FireCategory(mouseMove);
}

Window::Window(EventHandler& eventHandler_, bool resizable_, int width_, int height_, std::string title_) noexcept(false) : eventHandler { eventHandler_ }, resizable { resizable_ }, width { width_ }, height { height_ }, title { title_ }, lastXEvent{width_/2.0f}, lastYEvent{height_/2.0f}, lastX{width_/2.0f}, lastY{height_/2.0f}, mouseX{width_/2.0f}, mouseY{height_/2.0f} {
  // TODO: get errors from GLFW

  // Set resizable
  glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
  // Tell it to we do OpenGL (TODO: fix for Vulkan) TODO: do we need to call this _every_ window create
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // // Set opengl version TODO: every creation? really?
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
  // woo new window
  handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL); // TODO: figure out what these are
  // no window.
  if (!handle) {
    throw GraphicsCreateError("Failed to create a window");
  }
  // Point the window back to the window object
  glfwSetWindowUserPointer(handle, this);
  // Set the key-callback
  glfwSetKeyCallback(handle, KeyCallback);
  // set mouse-callback
  glfwSetCursorPosCallback(handle, MouseCallback);
}

// Window::Window(Window&& window) : handle { std::exchange(window.handle, nullptr) }, eventHandler { window.eventHandler }, resizable { window.resizable }, width { window.width }, height { window.height }, title { window.title } {
//   glfwSetWindowUserPointer(handle, this);
// }
//
// Window::Window(Window& window) : handle { std::exchange(window.handle, nullptr) }, eventHandler { window.eventHandler }, resizable { window.resizable }, width { window.width }, height { window.height }, title { window.title } {
//   glfwSetWindowUserPointer(handle, this);
// }

void Window::PollInputs() {
  glfwPollEvents();
}

bool Window::ShouldClose() {
  return glfwWindowShouldClose(handle);
}

void Window::UpdateBuffer() {
  glfwSwapBuffers(handle);
}

void Window::UpdateSituation() {
  lastX = mouseX;
  lastY = mouseY;
  glfwGetCursorPos(handle, &mouseX, &mouseY);
  if (firstMouse) {
    lastX = mouseX;
    lastY = mouseY;
  }
}

void Window::ActivateContext() {
  glfwMakeContextCurrent(handle);
}

void Window::CaptureCursor() {
  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::UncaptureCursor() {
  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::SetVsync(bool on) {
    ActivateContext();
    glfwSwapInterval(on);
}

Window::~Window() {
  // remember, handle is nullable
  // TODO: does glfwDestroyWindow do null checks?
  if (handle) {
    glfwDestroyWindow(handle);
  }
}

} // namespace origami::graphics
