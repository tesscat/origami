#include <origami/resources/shader.hpp>
#include <fstream>
#include <vector>
#include <glad/gl.h>
#include <utility>


namespace origami {
namespace resources {
VertexShader::VertexShader(std::filesystem::path filePath) noexcept(false) {
  // some sanity checking
  if (!std::filesystem::exists(filePath)) {
    throw ShaderCompilationError(filePath.string() + " does not exist!");
  }
  if (!std::filesystem::is_regular_file(filePath)) {
    throw ShaderCompilationError(filePath.string() + " is not a regular file!");
  }

  shader = glCreateShader(GL_VERTEX_SHADER);

  std::ifstream file;
  file.open(filePath);
  file.seekg(0, std::ios_base::end); // Seek to end of file.
  const unsigned int file_length = file.tellg();
  file.seekg(0);
  std::vector<char> file_data(file_length);
  file.read(&file_data[0], file_length);
  
  char* d1 = file_data.data();
  const std::string data = std::string(d1);
  const char* const s = data.c_str();

  glShaderSource(shader, 1, &s, NULL);
  glCompileShader(shader);

  file.close();

  int  success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    throw ShaderCompilationError(filePath.string() + ": " + infoLog);
  }
};

// TODO: dedup logic

VertexShader::~VertexShader() {
}

FragmentShader::FragmentShader(std::filesystem::path filePath) noexcept(false) {
  // some sanity checking
  if (!std::filesystem::exists(filePath)) {
    throw ShaderCompilationError(filePath.string() + " does not exist!");
  }
  if (!std::filesystem::is_regular_file(filePath)) {
    throw ShaderCompilationError(filePath.string() + " is not a regular file!");
  }

  shader = glCreateShader(GL_FRAGMENT_SHADER);

  std::ifstream file;
  file.open(filePath);
  file.seekg(0, std::ios_base::end); // Seek to end of file.
  const unsigned int file_length = file.tellg();
  file.seekg(0);
  std::vector<char> file_data(file_length);
  file.read(&file_data[0], file_length);

 char* d1 = file_data.data();
  const std::string data = std::string(d1);
  const char* const s = data.c_str();

  glShaderSource(shader, 1, &s, NULL);

  glCompileShader(shader);

  file.close();

  int  success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    throw ShaderCompilationError(filePath.string() + ": " + infoLog);
  }
};

FragmentShader::~FragmentShader() {
}

ShaderCompilationError::ShaderCompilationError(std::string err_) : err {err_} {};

const char *ShaderCompilationError::what() const noexcept {
  return err.c_str();
};

std::string ShaderPathPrefix() {
  return "shaders/glsl/";
}
} // namespace resources
}
