#include "origami/graphics/renderer.hpp"
#include "origami/resources/shader.hpp"
#include <origami/components/sprite.hpp>
#include <origami/log.hpp>

namespace origami {
namespace components {
Sprite::Sprite(origami::resources::Texture& texture_, unsigned int textureUnit, const char* uniformName, origami::components::Program program_) : texture {texture_}, sampler {texture, textureUnit, uniformName}, program {program_} {}

void Sprite::Submit(graphics::Renderer& renderer) {
  texture.Submit();
  program.Submit(renderer.viewId);
  transform.Apply(program);
  // transform.Apply();
  container.SetBuffers();
  // sampler.SetTexture();
}

Sprite& Sprite::operator=(Sprite&& other) {
  if (this != &other) {
    triangles = std::move(other.triangles);
    // verticies = std::move(other.verticies); TODO: can we move plz
    std::copy(&other.verticies[0], &other.verticies[3], verticies);
    container = std::move(other.container);
    transform = std::move(other.transform);
    texture = std::move(other.texture);
    sampler = std::move(other.sampler);
  }
  return *this;
}

Sprite& Sprite::operator=(const Sprite& other) {
  if (this != &other) {
    triangles = other.triangles;
    // verticies = other.verticies;
    std::copy(&other.verticies[0], &other.verticies[3], verticies);
    container = other.container;
    transform = other.transform;
    texture = other.texture;
    sampler = other.sampler;
  }
  return *this;
}

// TODO: proper init
Sprite::Sprite(Sprite&& other) : triangles {std::move(other.triangles)}, container {std::move(other.container)}, transform {std::move(other.transform)}, texture {other.texture}, sampler {std::move(other.sampler)}, program {std::move(other.program)} {
    std::copy(&other.verticies[0], &other.verticies[3], verticies);
  }

// Sprite::Sprite(const Sprite& other) : triangles {other.triangles}, verticies {other.verticies}, container {other.container}, transform {other.transform}, texture {other.texture}, sampler {other.sampler} {}
}
}
