#include "origami/graphics/renderer.hpp"
#include <origami/engine/init.hpp>
#include <origami/origami.hpp>

namespace origami {
App::App() {
  engine::engineInit();
}
App::~App() {
  engine::engineShutdown();
}
void App::Run() {
}
} // namespace origami
