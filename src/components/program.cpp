#include <origami/components/program.hpp>
#include <glad/gl.h>
#include <origami/log.hpp>

namespace origami {
namespace components {
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

};

void Program::SetInt(const std::string &name, int value) const { 
  glUniform1i(glGetUniformLocation(program, name.c_str()), value); 
}

void Program::Submit(uint64_t _view) {
  INFO("glUsingProgram");
  glUseProgram(program);
};
Program::~Program() {
  // bgfx::destroy(handle);
}
}
}
