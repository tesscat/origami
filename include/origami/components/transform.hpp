#ifndef ORIGAMI_COMPONENTS_TRANSFORM_HPP
#define ORIGAMI_COMPONENTS_TRANSFORM_HPP

// #include "bx/math.h"
#include "origami/components/program.hpp"
#include "origami/resources/shader.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>
#include <glm/matrix.hpp>

namespace origami {
namespace components {
class Transform {
public:
  // all units in radians kek
  // bx::Vec3 rotation = {0, 0, 0};
  // bx::Vec3 position = {0, 0, 0};
  glm::vec3 position = {0, 0, 0};
  glm::vec3 scale = {1.0f, 1.0f, 1.0f};
  glm::vec3 rotation = {0, 0, 0};

  glm::mat4 trans = glm::mat4(1.0f);

  // Apply the positions to the next rendered thing
  void Apply(origami::components::Program shader);
  // calculate the matrix
  void Calculate();
  // 
  // // TODO: other transforms
  // void RotateX(float value);
  // void RotateY(float value);
  // void RotateZ(float value);
};
}
}

#endif
