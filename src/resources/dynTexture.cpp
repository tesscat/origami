#include "origami/log.hpp"
#include "origami/resources/colour.hpp"
#include "origami/resources/superTexture.hpp"
#include <cstdlib>
#include <filesystem>
#include <glad/gl.h>
#include <memory>
#include <stdexcept>
#include <vector>
#include <origami/resources/dynTexture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


namespace origami {
namespace resources {
DynTexture::DynTexture(int width_, int height_) noexcept(false) : width{width_}, height{height_} {
    // data = std::vector<ColourBGRA32>(width*height);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    // glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenTextures(1, &texture);

    Refresh();
};

DynTexture::DynTexture(std::filesystem::path filePath) {
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // some sanity checking
    if (!std::filesystem::exists(filePath)) {
        throw std::runtime_error(filePath.string() + " does not exist!");
    }
    if (!std::filesystem::is_regular_file(filePath)) {
        throw std::runtime_error(filePath.string() + " is not a regular file!");
    }
    int nrChannels;
    // stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    uint8_t* imgdata = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    // uint8_t* imgdata = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    INFO("newer nrChannels {}", nrChannels);
    if (!imgdata) {
        throw std::runtime_error(filePath.string() + " did not load!");
    }
    // data = (ColourBGRA32*) imgdata;
    INFO("sz {}", sizeof(ColourBGRA32));
    INFO("nrCh {}", nrChannels);
    data = new ColourBGRA32[width*height];
    if (nrChannels == 4) {
        // comes out as RGBA
        for (int i = 0; i < width*height; i++) {
            data[i].red = imgdata[4*i];
            data[i].green = imgdata[4*i+1];
            data[i].blue = imgdata[4*i+2];
            data[i].alpha = imgdata[4*i+3];
        }
    } else if (nrChannels == 3) {
        for (int i = 0; i < width*height; i++) {
            data[i].red = imgdata[3*i];
            data[i].green = imgdata[3*i+1];
            data[i].blue = imgdata[3*i+2];
            data[i].alpha = 255;
        }
    } else {
        throw std::runtime_error("Unsupported image n_channels: " + filePath.string());
    }
    stbi_image_free(imgdata);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenTextures(1, &texture);
    //     glBindTexture(GL_TEXTURE_2D, texture);
    // // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, data);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
    // glGenerateMipmap(GL_TEXTURE_2D);
    //
    Refresh();

    
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
    // TODO: optimize by that one post
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, (uint8_t*)data);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

DynTexture::~DynTexture() {
    stbi_image_free(data);
}
}
}
