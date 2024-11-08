#include "origami/components/program.hpp"
#include "origami/log.hpp"
#include "origami/resources/texture.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>
#include <string>
#include <origami/graphics/window.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <origami/graphics/renderer.hpp>

#include <config.hpp>

#ifdef PLATFORM_NIX
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include <GLFW/glfw3native.h>

namespace origami {
namespace graphics {
RGBA::RGBA(float R_, float G_, float B_, float A_) : R{R_}, G{G_}, B{B_}, A{A_} {};


// constructor delegateion woooooooo
Renderer::Renderer(Window& window_) : Renderer(window_, RGBA(1.0, 1.0, 1.0, 1.0)) {}
Renderer::Renderer(Window& window_, RGBA clearColour_) : Renderer(window_, clearColour_, 0) {}
Renderer::Renderer(Window& window_, RGBA clearColour_, uint64_t viewId_): window {window_}, clearColour {clearColour_}, viewId {viewId_} {
  glfwMakeContextCurrent(window.handle);
  if (!gladLoadGL(glfwGetProcAddress)) {
    throw "No glad <3";
  }

  // proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  // proj = glm::ortho();
  // TODO: should put in clear??
  glEnable(GL_DEPTH_TEST); 

  SetViewport();
  Clear();
}

void Renderer::SetProjPerspective(float fov, float aspect_ratio, float near_clip, float far_clip) {
  proj = glm::perspective(fov, aspect_ratio, near_clip, far_clip);
}
void Renderer::SetProjOrtho(float width, float height, float near_clip, float far_clip) {
  proj = glm::ortho(-width/2.0f, width/2.0f, height/2.0f, -height/2.0f, near_clip, far_clip);
}

void Renderer::Clear() {
  glClearColor(clearColour.R, clearColour.G, clearColour.B, clearColour.A);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewport() {
  glViewport(0, 0, window.width, window.height);
}
//
// void Renderer::Render(abilities::Renderable& renderable, components::Program& program) {
//   renderable.Submit(viewId, program);
// }

void Renderer::Frame(std::vector<std::reference_wrapper<origami::components::Program>> programs) {
  // camPos.Calculate();
  
  // INFO("camera: {}/{}/{} {}/{}/{} {}/{}/{}", camPos.x, camPos.y, camPos.z, camFront.x, camFront.y, camFront.z, camUp.x, camUp.y, camUp.z);
  glm::mat4 view = glm::lookAt(camPos, camFront + camPos, camUp);
  // view = glm::translate(view, -camPos);
  // view = glm::rotate(view, -camFront[0], glm::vec3(1.0, 0.0, 0.0));
  // view = glm::rotate(view, -camFront[1], glm::vec3(0.0, 1.0, 0.0));
  // view = glm::rotate(view, -camFront[2], glm::vec3(0.0, 0.0, 1.0));
  // view *= -1.0f;
  for (origami::components::Program program: programs) {
    int loc = glGetUniformLocation(program.program, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
    loc = glGetUniformLocation(program.program, "proj");
    // proj = glm::scale(glm::mat4(1.0f), glm::vec3(0.9f));
    // SetProjOrtho();
    SetProjPerspective();
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));
    // loc = glGetUniformLocation(program.program, "camPos");
    // glUniformVec3fv(loc, 1, GL_FALSE, glm::value_ptr(proj));
  }
  // Clear();
}

// bx::Vec3 Renderer::ScreenCoordsToWorldSpace(float x, float y, float depth) {
//   // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords
//
//   // TODO: per-frame calc cacheing?
//   // get the inverse matrix
//   float view_x_proj[16];
//   bx::mtxMul(view_x_proj, view, proj);
//   bx::mtxInverse(inverse_view_proj, view_x_proj);
//
//   // apply it
//   float pos[4] = {x, y, depth, 1.0};
//   float res[4];
//   bx::vec4MulMtx(res, pos, inverse_view_proj);
//
//   // divide it all through by w
//   res[0] /= res[3];
//   res[1] /= res[3];
//   res[2] /= res[3];
//
//   return {res[0], res[1], res[2]};
// }

Renderer::~Renderer() {
  // bgfx::shutdown();
}
} // namespace graphics
}
