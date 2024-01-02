#ifndef ORIGAMI_GRAPHICS_VERTEX_HPP
#define ORIGAMI_GRAPHICS_VERTEX_HPP

#include <glad/gl.h>
#include <cstdint>
#include <vector>
#include <origami/components/program.hpp>
namespace origami {
namespace graphics {
struct PosNormalTexcoordVertex {
public:
  float x, y, z;
  // uint32_t rgba;
  float norm_x, norm_y, norm_z;
  float u, v;
  // PosColourVertex(float x, float y, float z, uint32_t rgba);

  const uint64_t AttribCount();
  const std::vector<float> Packed();
};

class PosTexcoordNormalVertexContainer {
public:
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  components::Program program;
  std::vector<PosNormalTexcoordVertex> posTexcoordVerticies;
  
  // TODO: do we need this
  std::vector<unsigned int> triangles;
  // std::vector<float> verticies;

  PosTexcoordNormalVertexContainer(std::vector<PosNormalTexcoordVertex> posColourVerticies, std::vector<unsigned int> triangles, components::Program program);
  ~PosTexcoordNormalVertexContainer();

  PosTexcoordNormalVertexContainer(const PosTexcoordNormalVertexContainer&) = delete;
  PosTexcoordNormalVertexContainer(PosTexcoordNormalVertexContainer&& container);

  PosTexcoordNormalVertexContainer& operator=(PosTexcoordNormalVertexContainer&& other);
  PosTexcoordNormalVertexContainer& operator=(const PosTexcoordNormalVertexContainer& other);

  void SetBuffers();
};
}
}

#endif
