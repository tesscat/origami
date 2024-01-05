#ifndef ORIGAMI_GRAPHICS_RENDERER_HPP
#define ORIGAMI_GRAPHICS_RENDERER_HPP

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <string>
#include <origami/components/transform.hpp>
#include <optional>
#include <origami/resources/shader.hpp>
#include <origami/resources/texture.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <origami/graphics/window.hpp>
#include <math.h>

namespace origami {
namespace graphics {
// Storage for the RGBA colourscheme
class RGBA {
public:
  float R, G, B, A;
  // uint32_t rgba;
  RGBA(float R, float G, float B, float A);
  // int ToHex();
};

class Renderer {
  Window& window;

  // bx::Vec3 at = {0, 0, 0};
  // bx::Vec3 eye = {0, 0, -5};
  // glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 proj;
public:
  glm::vec3 camPos = {0, 0, 0};
  glm::vec3 camFront = {0, 0, 1.0f};
  glm::vec3 camUp = {0, 1.0f, 0};
  uint64_t viewId;
  // float fov = 60;
  Renderer(Window& window);
  Renderer(Window& window, RGBA ClearColour);
  Renderer(Window& window, RGBA ClearColour, uint64_t view);

  ~Renderer();

  void SetProjPerspective(float fov = M_PI/4.0f, float aspect_ratio = 800.0f/600.0f, float near_clip = 0.1f, float far_clip = 100.0f);
  void SetProjOrtho(float width = 800.0f, float height = 600.0f, float near_clip = 0.1f, float far_clip = 100.0f);
  
  RGBA clearColour;
  void Clear();
  void SetViewport();

  // void Render(abilities::Renderable& renderable, components::Program& program);

  void Frame(std::vector<std::reference_wrapper<origami::components::Program>> programs);

  // bx::Vec3 ScreenCoordsToWorldSpace(float x, float y, float depth);
};
}
}

#endif
