#ifndef ORIGAMI_RESOURCES_TEXTURE_HPP
#define ORIGAMI_RESOURCES_TEXTURE_HPP

// #include <origami/graphics/texturesampler.hpp>
// #include <bgfx/bgfx.h>
#include "origami/components/program.hpp"
#include <exception>
#include <string>
#include <filesystem>
#include <origami/resources/textureInterface.hpp>

// namespace graphics {
// class TextureSampler;
// }

namespace origami {
namespace resources {
class Texture : public TextureInterface {
  unsigned int texture;
public:
  // bgfx::TextureHandle handle;
  Texture(std::filesystem::path filePath, std::string type) noexcept(false);
  ~Texture();

  void Submit(components::Program program);

  // graphics::TextureSampler CreateSampler(unsigned int textureUnit, std::string uniformName);

  // the class, e.g. specular or diffuse
  std::string type;
  std::filesystem::path path;
};

class TextureCompilationError : public std::exception {
  std::string err;
public:
  TextureCompilationError(std::string err_);
  const char* what() const noexcept override;
};

}
}

#endif
