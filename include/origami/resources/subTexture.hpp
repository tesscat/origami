#ifndef ORIGAMI_RESOURCES_SUBTEXTURE_HPP
#define ORIGAMI_RESOURCES_SUBTEXTURE_HPP

// #include <origami/graphics/dyntexturesampler.hpp>
// #include <bgfx/bgfx.h>
#include "glad/gl.h"
#include "origami/components/program.hpp"
#include "origami/resources/superTexture.hpp"
#include "origami/resources/textureInterface.hpp"
#include <cstdint>
#include <exception>
#include <memory>
#include <string>
#include <filesystem>
#include <vector>
#include <origami/resources/colour.hpp>

// namespace graphics {
// class DynTextureSampler;
// }

namespace origami {
namespace resources {
class SubTexture : public TextureInterface {
    int xoffsb, yoffsb, pX, pY;
    float relW, relH, relXOffs, relYOffs;
public:
    std::shared_ptr<SuperTexture> super;
    std::vector<ColourBGRA32> data;
    int height, width;
    // GLuint texture;
    // bgfx::DynTextureHandle handle;
    SubTexture(int height, int width, std::shared_ptr<SuperTexture> super);
    SubTexture(std::filesystem::path filePath, std::shared_ptr<SuperTexture> super);
    ~SubTexture();

    SubTexture(SubTexture&) = delete;
    SubTexture(SubTexture&&) = delete;

    void Refresh();
    void Submit(components::Program program);

    // graphics::DynTextureSampler CreateSampler(unsigned int dyntextureUnit, std::string uniformName);

    // the class, e.g. specular or diffuse
    std::string type;
    std::filesystem::path path;
};
}
}

#endif
