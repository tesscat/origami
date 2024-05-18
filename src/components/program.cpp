#include <origami/components/program.hpp>
#include <glad/gl.h>
#include <origami/log.hpp>

namespace origami {
namespace components {

TexOffsLocations::TexOffsLocations(unsigned int program) {
    txRelWidthLoc = glGetUniformLocation(program, "txRelWidth");
    txRelHeightLoc = glGetUniformLocation(program, "txRelHeight");
    txRelXOffsLoc = glGetUniformLocation(program, "txRelXOffs");
    txRelYOffsLoc = glGetUniformLocation(program, "txRelYOffs");
    txPxTexWidth = glGetUniformLocation(program, "txPxTexWidth");
    txPxTexHeight = glGetUniformLocation(program, "txPxTexHeight");
}
TexOffsLocations::TexOffsLocations() {}

Program::Program(resources::VertexShader &vertexShader_,
                 resources::FragmentShader &fragmentShader_) : vertexShader {vertexShader_}, fragmentShader {fragmentShader_} {
    program = glCreateProgram();
    glAttachShader(program, vertexShader.shader);
    glAttachShader(program, fragmentShader.shader);
    glLinkProgram(program);

    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw resources::ShaderCompilationError(std::string("program error: ") + infoLog);
    }

    locations = TexOffsLocations(program);

};

void Program::Submit(uint64_t _view) {
    glUseProgram(program);
};
Program::~Program() {
    // bgfx::destroy(handle);
}
}
}
