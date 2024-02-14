// #include <bgfx/bgfx.h>
#include "origami/components/program.hpp"
#include "origami/log.hpp"
#include <filesystem>
#include <origami/resources/texture.hpp>
#include <fstream>
#include <vector>
#include <stb/stb_image.h>
#include <glad/gl.h>


namespace origami {
namespace resources {
Texture::Texture(std::filesystem::path filePath, std::string type_) noexcept(false) : type {type_}, path {filePath} {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // some sanity checking
    if (!std::filesystem::exists(filePath)) {
        throw TextureCompilationError(filePath.string() + " does not exist!");
    }
    if (!std::filesystem::is_regular_file(filePath)) {
        throw TextureCompilationError(filePath.string() + " is not a regular file!");
    }
    int width, height, nrChannels;
    // stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    uint8_t* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    INFO("classic nrChannels {}", nrChannels);
    if (!data) {
        throw TextureCompilationError(filePath.string() + " did not load!");
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
};

void Texture::Submit(components::Program program) {
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1f(program.locations.txRelHeightLoc, 1.0f);
    glUniform1f(program.locations.txRelWidthLoc, 1.0f);
    glUniform1f(program.locations.txRelXOffsLoc, 0.0f);
    glUniform1f(program.locations.txRelYOffsLoc, 0.0f);

}

Texture::~Texture() {
    // bgfx::destroy(handle);
}

TextureCompilationError::TextureCompilationError(std::string err_) : err {err_} {};

const char *TextureCompilationError::what() const noexcept {
    return err.c_str();
};
}
}
