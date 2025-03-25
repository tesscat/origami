#ifndef ORIGAMI_RESOURCES_TEXTURE_HPP
#define ORIGAMI_RESOURCES_TEXTURE_HPP

// #include <origami/graphics/texturesampler.hpp>
// #include <bgfx/bgfx.h>
#include "origami/components/program.hpp"
#include "origami/resources/colour.hpp"
#include <exception>
#include <string>
#include <filesystem>
#include <origami/resources/textureInterface.hpp>
#include <vector>

// namespace graphics {
// class TextureSampler;
// }

namespace origami {
namespace resources {
class Texture : public TextureInterface {
    unsigned int texture;
public:
    std::vector<ColourBGRA32> data;
    int height, width;
    // bgfx::TextureHandle handle;
    Texture(std::filesystem::path filePath, std::string type) noexcept(false);
    ~Texture();
    void Refresh();
    void RefreshRange(int x0, int y0, int x1, int y2);
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
