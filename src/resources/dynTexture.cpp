#include <glad/gl.h>
#include <stdexcept>
#include <vector>
#include <origami/resources/dynTexture.hpp>


namespace origami {
namespace resources {
DynTexture::DynTexture(SuperTexture& super_, int width_, int height_) noexcept(false) : width{width_}, height{height_}, super{super_} {
    data = std::vector<ColourBGRA32>(width*height);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    if (super.bWidth < width || super.bHeight < height) {
        throw new std::length_error("width or height of supertex not sufficient");
    }
    auto pairs = super.Allocate();
    xoffsb = pairs.second.first;
    yoffsb = pairs.second.second;
    int pX = xoffsb * super.bWidth;
    int pY = yoffsb * super.bHeight;
    
    glTexSubImage2D(GL_TEXTURE_2D, 0, pX, pY, width, height, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, data.data());
};

void DynTexture::Submit(components::Program program) {
    super.Bind(xoffsb, yoffsb, program);
}

void DynTexture::Refresh() {

}

DynTexture::~DynTexture() {
    // bgfx::destroy(handle);
}
}
}
