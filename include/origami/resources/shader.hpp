#ifndef ORIGAMI_RESOURCES_SHADER_HPP
#define ORIGAMI_RESOURCES_SHADER_HPP

#include <exception>
#include <string>
#include <filesystem>

namespace origami {
namespace resources {
class VertexShader {
public:
  unsigned int shader;
  VertexShader(std::filesystem::path filePath) noexcept(false);
  ~VertexShader();
};
class FragmentShader {
public:
  unsigned int shader;
  FragmentShader(std::filesystem::path filePath) noexcept(false);
  ~FragmentShader();
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
