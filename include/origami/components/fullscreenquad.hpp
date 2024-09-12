#ifndef ORIGAMI_COMPONENTS_FULLSCREENQUAD_HPP
#define ORIGAMI_COMPONENTS_FULLSCREENQUAD_HPP

#include "origami/graphics/vertex.hpp"
#include <origami/components/program.hpp>
#include <origami/graphics/renderer.hpp>

#include <vector>

namespace origami {
namespace components {
class FullScreenQuad {
public:
    origami::graphics::PosNormalTexcoordVertex verticies[4] = {
        { 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     1.0f,      0.0f },
        { 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     1.0f,      1.0f },
        {-1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     0.0f,      1.0f },
        {-1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,     0.0f,      0.0f },
    };
    std::vector<unsigned int> triangles = {
        0,  1,  3,
        1,  2,  3,
    };
    origami::graphics::PosTexcoordNormalVertexContainer container = origami::graphics::PosTexcoordNormalVertexContainer(std::vector(&verticies[0], &verticies[4]), triangles);
    std::shared_ptr<origami::resources::TextureInterface> texture;

    FullScreenQuad(std::shared_ptr<origami::resources::TextureInterface> texture);

    void Submit(graphics::Renderer& renderer, components::Program program);
};
}
}

#endif
