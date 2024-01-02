#ifndef ORIGAMI_GRAPHICS_TEXTURE_SAMPLER_HPP
#define ORIGAMI_GRAPHICS_TEXTURE_SAMPLER_HPP

#include "origami/resources/texture.hpp"
namespace origami {
namespace graphics {
class TextureSampler {
  bool live = true;
public:
  resources::Texture& texture;
  // bgfx::UniformHandle uniformHandle;
  unsigned int textureUnit;
  // std::string uniformName;

  TextureSampler(resources::Texture& texture, unsigned int textureUnit, const char* uniformName);
  // TextureSampler(const TextureSampler&) = delete;
  // TextureSampler(TextureSampler &&);
  ~TextureSampler();

  TextureSampler& operator=(TextureSampler&& other);
  TextureSampler& operator=(const TextureSampler& other);
  TextureSampler(TextureSampler&&) = default;
  TextureSampler(const TextureSampler&) = default;

  void SetTexture();
};
}
}

#endif
