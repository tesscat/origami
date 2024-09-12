#ifndef ORIGAMI_RESOURCES_SSBO_HPP
#define ORIGAMI_RESOURCES_SSBO_HPP

#include "glad/gl.h"
#include <vector>

namespace origami {
namespace resources {
template<typename T>
class ShaderStorageBuffer {
public:
    std::vector<T> data;
    unsigned int ssbo;
    ShaderStorageBuffer(int size) : data(size) {
        glGenBuffers(1, &ssbo);
    }
    void FullRefresh(int flags = GL_DYNAMIC_READ) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        // glNamedBufferData(ssbo,
        glBufferData(
            GL_SHADER_STORAGE_BUFFER,
            sizeof(T) * data.size(),
            (const void*)data.data(),
            flags);
    }
    void PartialRefresh(int offset, int len) {
        // glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glNamedBufferSubData(ssbo,
                             offset,
                             len,
                             (const void*)data.data()
                             );
    }
    void Bind(int binding) {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, ssbo);
    }
};
}
}

#endif // !ORIGAMI_RESOURCES_SSBO_HPP
