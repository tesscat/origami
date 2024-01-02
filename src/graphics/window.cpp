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

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // TODO: optimise, this is a hot fn
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

Window::Window(EventHandler& eventHandler_, bool resizable_, int width_, int height_, std::string title_) noexcept(false) : eventHandler { eventHandler_ }, resizable { resizable_ }, width { width_ }, height { height_ }, title { title_ } {
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
}

Window::Window(Window&& window) : handle { std::exchange(window.handle, nullptr) }, eventHandler { window.eventHandler }, resizable { window.resizable }, width { window.width }, height { window.height }, title { window.title } {
  glfwSetWindowUserPointer(handle, this);
}

Window::Window(Window& window) : handle { std::exchange(window.handle, nullptr) }, eventHandler { window.eventHandler }, resizable { window.resizable }, width { window.width }, height { window.height }, title { window.title } {
  glfwSetWindowUserPointer(handle, this);
}

void Window::PollInputs() {
  glfwPollEvents();
}

bool Window::ShouldClose() {
  return glfwWindowShouldClose(handle);
}

void Window::UpdateBuffer() {
  INFO("swapping window buffers");
  glfwSwapBuffers(handle);
}

void Window::ActivateContext() {
  glfwMakeContextCurrent(handle);
}

Window::~Window() {
  // remember, handle is nullable
  // TODO: does glfwDestroyWindow do null checks?
  if (handle) {
    glfwDestroyWindow(handle);
  }
}

} // namespace origami::graphics
