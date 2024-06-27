#ifndef ORIGAMI_RESOURCES_DYNTEXTURE_HPP
#define ORIGAMI_RESOURCES_DYNTEXTURE_HPP

#include "origami/components/program.hpp"
#include "origami/resources/colour.hpp"
#include <exception>
#include <string>
#include <filesystem>
#include <origami/resources/textureInterface.hpp>
#include <vector>

namespace origami {
namespace resources {
class DynTexture : public TextureInterface {
    unsigned int texture;
public:
    std::vector<ColourBGRA32> data;
    int height, width;
    // bgfx::TextureHandle handle;
    DynTexture(int width, int height);
    ~DynTexture();
    void Refresh();
    void RefreshRange(int x0, int y0, int x1, int y2);
    void Submit(components::Program program);

    // graphics::TextureSampler CreateSampler(unsigned int textureUnit, std::string uniformName);

    // the class, e.g. specular or diffuse
    std::string type;
    std::filesystem::path path;
};

}
}


#endif // !ORIGAMI_RESOURCES_DYNTEXTURE_HPP
