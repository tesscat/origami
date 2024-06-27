#include "origami/components/program.hpp"
#include "origami/log.hpp"
#include "origami/resources/shader.hpp"
#include "origami/resources/texture.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>
#include <stdexcept>
#include <string>
#include <origami/graphics/window.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <origami/graphics/renderer.hpp>

#include <config.hpp>

#ifdef PLATFORM_NIX
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include <GLFW/glfw3native.h>

namespace origami {
namespace graphics {
RGBA::RGBA(float R_, float G_, float B_, float A_) : R{R_}, G{G_}, B{B_}, A{A_} {};


// constructor delegateion woooooooo
Renderer::Renderer(Window& window, float width, float height) : Renderer(window, width, height, RGBA(1.0, 0.5, 1.0, 1.0)) {}
Renderer::Renderer(Window& window, float width, float height, RGBA clearColour_) : Renderer(window, width, height, clearColour_, 0) {}
Renderer::Renderer(Window& window, float width_, float height_, RGBA clearColour_, uint64_t viewId_): width{width_}, height{height_}, clearColour {clearColour_}, viewId {viewId_} {
    glfwMakeContextCurrent(window.handle);
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw "No glad <3";
    }
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // texture version (default)
    glGenTextures(1, &colourAttachment);
    glBindTexture(GL_TEXTURE_2D, colourAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colourAttachment, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Failed to create a complete FBO");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::SetProjPerspective(float fov, float aspect_ratio, float near_clip, float far_clip) {
    proj = glm::perspective(fov, aspect_ratio, near_clip, far_clip);
}
void Renderer::SetProjOrtho(float width_, float height_, float near_clip, float far_clip) {
    proj = glm::ortho(-width_/2.0f, width_/2.0f, height_/2.0f, -height_/2.0f, near_clip, far_clip);
}

void Renderer::Clear() {
    glClearColor(clearColour.R, clearColour.G, clearColour.B, clearColour.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glEnable(GL_DEPTH_TEST); 
}

void Renderer::PreFrame(std::vector<std::reference_wrapper<origami::components::Program>> programs) {
    Bind();
    Clear();
    glViewport(0, 0, width, height);

    glm::mat4 view = glm::lookAt(camPos, camFront + camPos, camUp);

    for (origami::components::Program program: programs) {
        int loc = glGetUniformLocation(program.program, "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
        loc = glGetUniformLocation(program.program, "proj");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));
    }
}

void Renderer::FinalizeFrame(Window& window, int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

Renderer::~Renderer() {
    glDeleteFramebuffers(1, &fbo);
}
} // namespace graphics
} // namespace origami
