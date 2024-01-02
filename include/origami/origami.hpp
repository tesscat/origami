#ifndef ORIGAMI_ORIGAMI_HPP
#define ORIGAMI_ORIGAMI_HPP

#include <origami/graphics/renderer.hpp>
#include <vector>
#include <origami/graphics/window.hpp>
#include <origami/events/firer.hpp>
#include <origami/events/event.hpp>
#include <origami/components/program.hpp>
#include <origami/components/transform.hpp>
#include <origami/components/sprite.hpp>
#include <origami/log.hpp>

// #include <entt/entt.hpp>

#include <optional>

// MASSIVE TODO: make multithreaded

namespace origami {
class App {
  // EventFirer<EngineInit> engineInitEvent;
public:  
  EventHandler eventHandler;
  // entt::registry registry;
  // std::vector<graphics::Window> windows;
  // std::vector<resources::Shader> shaders;
  // std::vector<graphics::ShaderProgram> shaderPrograms;
  // std::vector<graphics::Verticies> meshes;
  // TODO: multiple-renderers?;
  // std::optional<graphics::Renderer> renderer;
  App();
  virtual ~App();
  virtual void Run();

  void InitialiseRenderer(graphics::Window &window) noexcept(false);
};
}

#endif
