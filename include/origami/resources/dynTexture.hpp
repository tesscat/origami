#ifndef ORIGAMI_RESOURCES_DYNTEXTURE_HPP
#define ORIGAMI_RESOURCES_DYNTEXTURE_HPP

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
class DynTexture : public TextureInterface {
    int xoffsb, yoffsb, pX, pY;
    float relW, relH, relXOffs, relYOffs;
public:
    std::shared_ptr<SuperTexture> super;
    std::vector<ColourBGRA32> data;
    int height, width;
    // GLuint texture;
    // bgfx::DynTextureHandle handle;
    DynTexture(int height, int width, std::shared_ptr<SuperTexture> super);
    DynTexture(std::filesystem::path filePath, std::shared_ptr<SuperTexture> super);
    ~DynTexture();

    DynTexture(DynTexture&) = delete;
    DynTexture(DynTexture&&) = delete;

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
