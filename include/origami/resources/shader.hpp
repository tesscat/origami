#ifndef ORIGAMI_RESOURCES_SHADER_HPP
#define ORIGAMI_RESOURCES_SHADER_HPP

#include "origami/components/program.hpp"
#include "origami/resources/textureInterface.hpp"
#include <origami/resources/ubo.hpp>
#include <glad/gl.h>
#include <exception>
#include <string>
#include <filesystem>

namespace origami {
namespace resources {
class Shader {
public:
    unsigned int shader;
    Shader(std::filesystem::path filePath, GLenum shaderType) noexcept(false);
};

class VertexShader : public Shader {
public:
  VertexShader(std::filesystem::path filePath) noexcept(false);
  ~VertexShader();
};
class FragmentShader : public Shader {
public:
  FragmentShader(std::filesystem::path filePath) noexcept(false);
  ~FragmentShader();
};

class ComputeShader2D : public Shader, public TextureInterface {
public:
    unsigned int program;
    unsigned int texOutput;
    unsigned int x,y;
    ComputeShader2D(std::filesystem::path filePath, unsigned int x, unsigned int y) noexcept(false);
    ~ComputeShader2D();

    void Dispatch();
    // Awaits the Memory Barrier
    void Await();

    virtual void Submit(components::Program program) override;
    GLint GetUniformLocation(const char* uniform);
    // template<typename T>
    // void BindUBO(GLint binding, UBO<T> ubo) {
        // glBindBufferBase(GL_UNIFORM_BUFFER, binding, ubo.handle);
    // }
};

class ShaderCompilationError : public std::exception {
  std::string err;
public:
  ShaderCompilationError(std::string err_);
  const char* what() const noexcept override;
};

std::string ShaderPathPrefix();
}
}

#endif
