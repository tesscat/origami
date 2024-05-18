#ifndef ORIGAMI_COMPONENTS_PROGRAM_HPP
#define ORIGAMI_COMPONENTS_PROGRAM_HPP

#include <origami/resources/shader.hpp>

namespace origami {
namespace components {
struct TexOffsLocations {
    unsigned int txRelXOffsLoc;
    unsigned int txRelYOffsLoc;
    unsigned int txRelWidthLoc;
    unsigned int txRelHeightLoc;
    unsigned int txPxTexWidth;
    unsigned int txPxTexHeight;

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

    // std::vector<bgfx::UniformHandle> uniforms;
    Program(resources::VertexShader &vertexShader, resources::FragmentShader &fragmentShader);
    virtual ~Program();
    void Submit(uint64_t view);
    // void AddSampler(graphics::TextureSampler sampler);
};
}
}

#endif
