#ifndef ORIGAMI_GRAPHICS_WINDOW_HPP
#define ORIGAMI_GRAPHICS_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <origami/events/firer.hpp>
// need to include glad before glfw3
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
#include <exception>
#include <string>

namespace origami {
namespace graphics {
  /**
   * * @brief The error callback for GLFW. This function is _only_ called by GLFW and you should not call it
   * *
   * * @param i The error code
   * * @param c The error text
   * */
void glfwErrorCallback(int i, const char* c) noexcept(false);

class GraphicsCreateError : public std::exception {
  std::string err;
public:
  /**
   * @brief Construct a WindowCreateError with the given text
   *
   * @param err The text to use
   */
  GraphicsCreateError(std::string err);
  const char* what() const noexcept override;
};

class GLFWErr : public std::exception {
  std::string err;
public:
  /**
   * @brief Construct a GLFWErr with  the given text
   *
   * @param err_ The text to use
   */
  GLFWErr(std::string err_);
  const char* what() const noexcept override;
};

class Window {

  /**
   * @brief The keyy callback that is called for every key interaction
   *
   * @param window The window it was called for
   * @param key The key that was pressed
   * @param scancode The scancode for the key
   * @param action The GLFW action for the key
   * @param mods Any modifier keys
   */
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  EventHandler& eventHandler;
public:
  /// NULLABLE
  GLFWwindow* handle;
  /**
   * @brief Construct a window with the given attributes, and create an actual window object
   *
   * @param eventHandler The event-handler that should handle events for this window
   * @param resizeable Whether this window should be resizable
   * @param width The initial width of the window
   * @param height The initial height of the window
   * @param title The textual title of the window
   */
  Window(EventHandler& eventHandler, bool resizeable, int width, int height, std::string title) noexcept(false);
  Window(Window&& window);
  Window(Window& window);
  ~Window();

  // TODO: setters & getters

  /**
   * @brief Poll inputs - this handles inputs for _every_ window currently existing
   */
  static void PollInputs();
  /**
   * @brief Whether the window should close (has had an X button pressed, was closed via keybind etc)
   *
   * @return Whether or not it should close
   */
  bool ShouldClose();

  /**
   * @brief Updates the render buffer by calling glfwSwapRenderBuffer
   */
  void UpdateBuffer();

  /**
   * @brief Makes the context of this window the current context
   */
  void ActivateContext();
  
  // Read-only
  bool resizable = false;
  // Read-only
  int width, height;
  // Read-only
  std::string title;
};
}
}

#endif
