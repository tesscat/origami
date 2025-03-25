#include <origami/graphics/window.hpp>

#include <origami/engine/init.hpp>
#include <origami/log.hpp>

namespace origami {
namespace engine {
void engineInit() noexcept(false) {
  INFO("Origami initialised");
  glfwSetErrorCallback(origami::graphics::glfwErrorCallback);
  if(!glfwInit()) {
    throw origami::graphics::GLFWErr("Failed to intitialse GLFW");
  }
}

void engineShutdown() noexcept(false) {
  glfwTerminate();
  INFO("Origami shutdown");
}
}
}
