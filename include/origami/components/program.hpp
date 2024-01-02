#ifndef ORIGAMI_COMPONENTS_PROGRAM_HPP
#define ORIGAMI_COMPONENTS_PROGRAM_HPP

#include "origami/resources/texture.hpp"
#include <string>
#include <vector>
#include <origami/resources/shader.hpp>

namespace origami {
namespace components {
class Program {
public:
  resources::VertexShader& vertexShader;
  resources::FragmentShader& fragmentShader;
  // graphics::PosTexcoordNormalVertexContainer& container;
  // TODO: should prolly detach vertex data from program so one prog can render many things
  unsigned int program;

  // std::vector<bgfx::UniformHandle> uniforms;
  Program(resources::VertexShader &vertexShader, resources::FragmentShader &fragmentShader);
  virtual ~Program();
  void SetInt(const std::string &name, int value) const;
  void Submit(uint64_t view);
  // void AddSampler(graphics::TextureSampler sampler);
};
}
}

#endif
