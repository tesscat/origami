#ifndef ORIGAMI_COMPONENTS_PROGRAM_HPP
#define ORIGAMI_COMPONENTS_PROGRAM_HPP

#include <vector>
#include <stdint.h>

namespace origami {
// forward defs to not header loop
namespace resources {
class VertexShader;
class FragmentShader;
}
namespace components {
struct TexOffsLocations {
    unsigned int txRelXOffsLoc;
    unsigned int txRelYOffsLoc;
    unsigned int txRelWidthLoc;
    unsigned int txRelHeightLoc;
    unsigned int txPxTexWidth;
    unsigned int txPxTexHeight;

    unsigned int proj;
    unsigned int view;
    unsigned int transform;

    TexOffsLocations(unsigned int program);
    TexOffsLocations();
};


class Program {
public:
    resources::VertexShader& vertexShader;
    resources::FragmentShader& fragmentShader;
    // graphics::PosTexcoordNormalVertexContainer& container;
    // TODO: should prolly detach vertex data from program so one prog can render many things
    unsigned int program;
    TexOffsLocations locations;
    // UniformLocations uniformLocations;

    // std::vector<bgfx::UniformHandle> uniforms;
    Program(resources::VertexShader &vertexShader, resources::FragmentShader &fragmentShader);
    virtual ~Program();
    void Submit();
    // void AddSampler(graphics::TextureSampler sampler);
};
}
}

#endif
