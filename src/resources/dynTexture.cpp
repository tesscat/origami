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
// DynTexture::DynTexture(int width_, int height_) noexcept(false) : width{width_}, height{height_} {
//     // data = std::vector<ColourBGRA32>(width*height);
//
//     // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
//     // glGenerateMipmap(GL_TEXTURE_2D);
//
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//     glGenTextures(1, &texture);
//
//     Refresh();
// };

DynTexture::DynTexture(std::filesystem::path filePath, std::shared_ptr<SuperTexture> super_) : super{super_} {
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
    if (!imgdata) {
        throw std::runtime_error(filePath.string() + " did not load!");
    }
    
    if (super->bWidth < width || super->bHeight < height) {
        throw new std::length_error("width or height of supertex not sufficient");
    }
    // data = (ColourBGRA32*) imgdata;
    // data = new ColourBGRA32[width*height];
    data = std::vector<ColourBGRA32>(width*height);
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

    auto pairs = super->Allocate();
    xoffsb = pairs.second.first;
    yoffsb = pairs.second.second;
    pX = xoffsb * super->bWidth;
    pY = yoffsb * super->bHeight;
    relW = (float)width/super->fullWidth;
    relH = (float)height/super->fullHeight;
    relXOffs = xoffsb*super->relWidth;
    relYOffs = yoffsb*super->relHeight;

    Refresh();
};

DynTexture::DynTexture(int width_, int height_, std::shared_ptr<SuperTexture> super_) : super{super_}, width{width_}, height{height_} {
    data = std::vector<ColourBGRA32>(width*height);

    auto pairs = super->Allocate();
    xoffsb = pairs.second.first;
    yoffsb = pairs.second.second;
    pX = xoffsb * super->bWidth;
    pY = yoffsb * super->bHeight;
    relW = (float)width/super->fullWidth;
    relH = (float)height/super->fullHeight;
    relXOffs = xoffsb*super->relWidth;
    relYOffs = yoffsb*super->relHeight;

    Refresh();
};

void DynTexture::Submit(components::Program program) {
    super->BindRaw();
    // glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1f(program.locations.txRelHeightLoc, relW);
    glUniform1f(program.locations.txRelWidthLoc, relH);
    glUniform1f(program.locations.txRelXOffsLoc, relXOffs);
    glUniform1f(program.locations.txRelYOffsLoc, relYOffs);
    glUniform1f(program.locations.txPxTexWidth, width);
    glUniform1f(program.locations.txPxTexHeight, height);

    // glUniform1f(program.locations.txRelHeightLoc, 1.0f);
    // glUniform1f(program.locations.txRelWidthLoc, 1.0f);
    // glUniform1f(program.locations.txRelXOffsLoc, 0.0f);
    // glUniform1f(program.locations.txRelYOffsLoc, 0.0f);
}

void DynTexture::Refresh() {
    super->BindRaw();
    // glBindTexture(GL_TEXTURE_2D, texture);
    // TODO: optimize by that one post
    glTexSubImage2D(GL_TEXTURE_2D, 0, pX, pY, width, height, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, (uint8_t*)data.data());
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

DynTexture::~DynTexture() {
}
}
}
