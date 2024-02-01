#ifndef ORIGAMI_RESOURCES_DYNTEXTURE_HPP
#define ORIGAMI_RESOURCES_DYNTEXTURE_HPP

// #include <origami/graphics/dyntexturesampler.hpp>
// #include <bgfx/bgfx.h>
#include "origami/components/program.hpp"
#include "origami/resources/superTexture.hpp"
#include <cstdint>
#include <exception>
#include <string>
#include <filesystem>
#include <vector>
#include <origami/resources/colour.hpp>

// namespace graphics {
// class DynTextureSampler;
// }

namespace origami {
namespace resources {
class DynTexture {
    SuperTexture& super;
    int xoffsb, yoffsb;
public:
    std::vector<ColourBGRA32> data;
    int height, width;
    // bgfx::DynTextureHandle handle;
    DynTexture(SuperTexture& super, int height, int width) noexcept(false);
    ~DynTexture();

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
