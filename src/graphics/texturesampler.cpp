// #include "bgfx/bgfx.h"
#include "origami/log.hpp"
#include <origami/graphics/texturesampler.hpp>

namespace origami {
namespace graphics {
TextureSampler::TextureSampler(resources::Texture& texture_, unsigned int textureUnit_, const char* uniformName) : texture {texture_}, textureUnit {textureUnit_} {
  // uniformHandle = bgfx::createUniform(uniformName, bgfx::UniformType::Sampler);
}
TextureSampler::~TextureSampler() {
  if (live) {}
    // bgfx::destroy(uniformHandle);
}

void TextureSampler::SetTexture() {
  // bgfx::setTexture(textureUnit, uniformHandle, texture.handle);
}

TextureSampler& TextureSampler::operator=(TextureSampler&& other) {
  if (this != &other) {
    texture = other.texture;
    // uniformHandle = other.uniformHandle;
    textureUnit = other.textureUnit;
  }
  return *this;
}

TextureSampler& TextureSampler::operator=(const TextureSampler& other) {
  if (this != &other) {
    texture = other.texture;
    // uniformHandle = other.uniformHandle;
    textureUnit = other.textureUnit;
  }
  return *this;
}

} // namespace graphics
}
