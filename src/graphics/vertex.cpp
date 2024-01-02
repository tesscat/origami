#include <origami/graphics/vertex.hpp>
#include <origami/log.hpp>
// float vertices[] = {
//   1.0f,  1.0f, 0.0f,  // top right
//   1.0f, -1.0f, 0.0f,  // bottom right
//   -1.0f, -1.0f, 0.0f,  // bottom left
//   -1.0f,  1.0f, 0.0f   // top left 
// };
// unsigned int indices[] = {  // note that we start from 0!
//   0, 1, 3,  // first Triangle
//   1, 2, 3   // second Triangle
// };
namespace origami {
namespace graphics {
const uint64_t PosNormalTexcoordVertex::AttribCount() {return 8;}
const std::vector<float> PosNormalTexcoordVertex::Packed() {
  return std::vector({x, y, z}); // , norm_x, norm_y, norm_z, u, v});
}

PosTexcoordNormalVertexContainer::PosTexcoordNormalVertexContainer(
    std::vector<PosNormalTexcoordVertex> posColourVerticies_, std::vector<unsigned int> triangles_, components::Program program_) : posTexcoordVerticies {posColourVerticies_}, triangles {triangles_}, program{program_} {
  // for (auto vertex: posTexcoordVerticies) {
  //   INFO("V");
  //   std::vector<float> packed = vertex.Packed();
  //   verticies.insert(verticies.end(), packed.begin(), packed.end());
  // }
  //
  // for (float v : verticies) {
  //   INFO("float {}", v);
  // }


  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(PosNormalTexcoordVertex) * posTexcoordVerticies.size(), &posTexcoordVerticies.front(), GL_STATIC_DRAW);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticies.size(), &verticies.front(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triangles.size(), &triangles[0], GL_STATIC_DRAW);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, sizeof(PosNormalTexcoordVertex), (void*)0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6* sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  // program.Submit(0); // TODO: view

  glBindVertexArray(0);
}

PosTexcoordNormalVertexContainer::PosTexcoordNormalVertexContainer(PosTexcoordNormalVertexContainer&& container) : /* vertexLayout {container.vertexLayout}, */ /* vbh {container.vbh}, ibh {container.ibh}, */ posTexcoordVerticies {container.posTexcoordVerticies}, triangles {container.triangles}, program{container.program} {
  // container.ibh = BGFX_INVALID_HANDLE;
  // container.vbh = BGFX_INVALID_HANDLE;
}

PosTexcoordNormalVertexContainer::~PosTexcoordNormalVertexContainer() {
  // bgfx::destroy(ibh);
  // bgfx::destroy(vbh);
}

void PosTexcoordNormalVertexContainer::SetBuffers() {
  INFO("setting buffers");
  // program.Submit(0);
  glBindVertexArray(VAO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  // glDrawArrays()
}

PosTexcoordNormalVertexContainer& PosTexcoordNormalVertexContainer::operator=(PosTexcoordNormalVertexContainer&& other) {
  // TODO: big; make move not copy assignment maybe
  if (this != &other) {
    // vertexLayout = other.vertexLayout;
    // vbh = other.vbh;
    // ibh = other.ibh;
    posTexcoordVerticies = other.posTexcoordVerticies;
    triangles = other.triangles;
  }
  return *this;
}
PosTexcoordNormalVertexContainer& PosTexcoordNormalVertexContainer::operator=(const PosTexcoordNormalVertexContainer& other) {
  // TODO: big; make move not copy assignment maybe
  if (this != &other) {
    // vertexLayout = other.vertexLayout;
    // vbh = other.vbh;
    // ibh = other.ibh;
    posTexcoordVerticies = other.posTexcoordVerticies;
    triangles = other.triangles;
  }
  return *this;
}
}
}
