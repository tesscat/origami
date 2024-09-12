#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "origami/components/program.hpp"
#include "origami/graphics/renderer.hpp"
#include "origami/resources/shader.hpp"
#include <origami/components/fullscreenquad.hpp>
#include <origami/log.hpp>

const glm::mat4 id(1.0f);
const float* idptr = glm::value_ptr(id);

namespace origami {
namespace components {
FullScreenQuad::FullScreenQuad(std::shared_ptr<origami::resources::TextureInterface> texture_) : texture {texture_} {}

void FullScreenQuad::Submit(graphics::Renderer& renderer, components::Program program) {
    program.Submit();
    texture->Submit(program);
    // Set view/proj uniforms
    // renderer.Apply(program);
    // require identity transforms 
    glUniformMatrix4fv(program.locations.view, 1, GL_FALSE, idptr);
    glUniformMatrix4fv(program.locations.proj, 1, GL_FALSE, idptr);
    glUniformMatrix4fv(program.locations.transform, 1, GL_FALSE, idptr);
    container.SetBuffers();
}
}
}
