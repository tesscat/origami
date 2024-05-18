#ifndef ORIGAMI_GRAPHICS_RENDERER_HPP
#define ORIGAMI_GRAPHICS_RENDERER_HPP

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <string>
#include <origami/components/transform.hpp>
#include <optional>
#include <origami/resources/shader.hpp>
#include <origami/resources/texture.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <origami/graphics/window.hpp>
#include <math.h>

namespace origami {
namespace graphics {
// Storage for the RGBA colourscheme
class RGBA {
public:
    float R, G, B, A;
    // uint32_t rgba;
    RGBA(float R, float G, float B, float A);
    // int ToHex();
};

class Renderer {
    // Window& window;

    // bx::Vec3 at = {0, 0, 0};
    // bx::Vec3 eye = {0, 0, -5};
    // glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj;
    unsigned int fbo;
    unsigned int colourAttachment, depthStencilAttachment;
    float width, height;
public:
    glm::vec3 camPos = {0, 0, 0};
    glm::vec3 camFront = {0, 0, 1.0f};
    glm::vec3 camUp = {0, 1.0f, 0};
    uint64_t viewId;
    // float fov = 60;
    Renderer(Window& window, float height, float width);
    Renderer(Window& window, float height, float width, RGBA ClearColour);
    Renderer(Window& window, float height, float width, RGBA ClearColour, uint64_t view);

    ~Renderer();

    void SetProjPerspective(float fov = M_PI/4.0f, float aspect_ratio = 800.0f/600.0f, float near_clip = 0.1f, float far_clip = 100.0f);
    void SetProjOrtho(float width, float height, float near_clip = 0.1f, float far_clip = 100.0f);

    RGBA clearColour;
    void Clear();

    // void Render(abilities::Renderable& renderable, components::Program& program);

    void PreFrame(std::vector<std::reference_wrapper<origami::components::Program>> programs);
    void FinalizeFrame(Window& window, int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1);
    inline void FinalizeFrame(Window& window) {FinalizeFrame(window, 0, 0, width, height, 0, 0, window.width, window.height);}
    void Bind();

    // bx::Vec3 ScreenCoordsToWorldSpace(float x, float y, float depth);
};
}
}

#endif
