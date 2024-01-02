#ifndef ORIGAMI_COMPONENTS_SPRITE_HPP
#define ORIGAMI_COMPONENTS_SPRITE_HPP

// #include <bgfx/bgfx.h>
#include "origami/graphics/texturesampler.hpp"
#include "origami/graphics/vertex.hpp"
#include <string>
#include <origami/components/program.hpp>
#include <origami/resources/shader.hpp>
#include <origami/graphics/renderer.hpp>
#include <origami/components/transform.hpp>

#include <vector>

namespace origami {
namespace components {
class Sprite {
public:
  origami::graphics::PosNormalTexcoordVertex verticies[4] = {
    { 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     1.0f,      0.0f },
    { 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     1.0f,      1.0f },
    {-1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     0.0f,      1.0f },
    {-1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     0.0f,      0.0f },
  };
  std::vector<unsigned int> triangles = {
    0,  1,  3,
    1,  2,  3,
  };
  origami::components::Program program;
  origami::graphics::PosTexcoordNormalVertexContainer container = origami::graphics::PosTexcoordNormalVertexContainer(std::vector(&verticies[0], &verticies[4]), triangles, program);
  origami::components::Transform transform;
  origami::resources::Texture& texture;
  origami::graphics::TextureSampler sampler;
  //
  Sprite(Sprite&&);
  Sprite& operator=(Sprite&& other);
  Sprite& operator=(const Sprite& other);
  // Sprite(const Sprite&);
  
  // ~Sprite() = default;

  Sprite(origami::resources::Texture& texture, unsigned int textureUnit, const char* uniformName, origami::components::Program program);

  void Submit(graphics::Renderer& renderer);
};
}
}

#endif
