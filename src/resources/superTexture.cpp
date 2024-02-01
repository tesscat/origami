#include "glad/gl.h"
#include "origami/components/program.hpp"
#include <origami/resources/colour.hpp>
#include <cstdlib>
#include <origami/resources/superTexture.hpp>

namespace origami::resources {
SuperTexture::SuperTexture(int bWidth_, int bHeight_, int bX_, int bY_) : bX{bX_}, bY{bY_}, bHeight{bHeight_}, bWidth{bWidth_}, blocksCount{bX_*bY_} {
    blocks = std::vector<bool>(bX*bY, false);
    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    fullWidth = bWidth * bX;
    fullHeight = bHeight * bY;
    relWidth = 1.0f/bX;
    relHeight = 1.0f/bY;
    void* blank_space = calloc(fullWidth*fullHeight, sizeof(ColourBGRA32));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fullWidth, fullHeight, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, blank_space);
    free(blank_space);
}

std::pair<int, std::pair<int, int>> SuperTexture::Allocate() {
    // TODO: make better
    int id = 0;
    while (blocks[id] && id < blocksCount) {id++;}
    if (id == blocksCount) {
        throw new std::bad_alloc();
    }
    blocks[id] = true;
    // ordering is across then down one
    // and integer division always truncates (rounds down)
    int pX = id % bX;
    int pY = id/bX;

    return std::make_pair(id, std::make_pair(pX, pY));
}

void SuperTexture::Deallocate(int id) {
    if (id < blocksCount) blocks[id] = false;
}

void SuperTexture::BindRaw() {
    glBindTexture(GL_TEXTURE_2D, texHandle);
}

void SuperTexture::Bind(int x, int y, components::Program program) {
    float relXOffs = relWidth*x;
    float relYOffs = relHeight*y;

    glUniform1f(program.locations.txRelXOffsLoc, relXOffs);
    glUniform1f(program.locations.txRelYOffsLoc, relYOffs);
    glUniform1f(program.locations.txRelWidthLoc, relWidth);
    glUniform1f(program.locations.txRelHeightLoc, relHeight);
}

}
