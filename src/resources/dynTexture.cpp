// #include <bgfx/bgfx.h>
#include "origami/components/program.hpp"
#include "origami/log.hpp"
#include <filesystem>
#include <origami/resources/dynTexture.hpp>
#include <fstream>
#include <vector>
#include <stb/stb_image.h>
#include <glad/gl.h>


namespace origami {
namespace resources {
DynTexture::DynTexture(int width_, int height_) : width{width_}, height{height_}, data{static_cast<size_t>(width_*height_)}{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // some sanity checking
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

};

void DynTexture::Submit(components::Program program) {
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1f(program.locations.txRelHeightLoc, 1.0f);
    glUniform1f(program.locations.txRelWidthLoc, 1.0f);
    glUniform1f(program.locations.txRelXOffsLoc, 0.0f);
    glUniform1f(program.locations.txRelYOffsLoc, 0.0f);

}

void DynTexture::Refresh() {
    glBindTexture(GL_TEXTURE_2D, texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // TODO: optimize by that one post
    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.data());
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
DynTexture::~DynTexture() {
    // bgfx::destroy(handle);
}

}
}
