// #include <bgfx/bgfx.h>
// #include <bx/math.h>
#include "origami/components/program.hpp"
#include "origami/log.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <origami/components/transform.hpp>
#include <glad/gl.h>

namespace origami {
namespace components {
void Transform::Calculate() {
  // std::vector<float> matrix = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  // bx::mtxRotateXYZ(matrix.data(), rotation.x, rotation.y, rotation.z);
  // bx::mtxTranslate(matrix.data(), position.x, position.y, position.z);
  // return matrix;
  trans = glm::mat4(1.0f);
  trans = glm::translate(trans, position);
  trans = glm::scale(trans, scale);
  trans = glm::rotate(trans, rotation[0], glm::vec3(1.0, 0.0, 0.0));
  trans = glm::rotate(trans, rotation[1], glm::vec3(0.0, 1.0, 0.0));
  trans = glm::rotate(trans, rotation[2], glm::vec3(0.0, 0.0, 1.0));
}

void Transform::Apply(origami::components::Program program) {
  unsigned int transLoc = glGetUniformLocation(program.program, "transform");
  // trans = glm::mat4(1.0f);
  // trans = glm::translate(trans, glm::vec3(0.1f, 0.1f, 0.0f));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
  // Calculate();
  // bgfx::setTransform(Calculate().data());
}

}
}
