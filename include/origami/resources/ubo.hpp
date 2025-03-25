#include "glad/gl.h"
namespace origami {
namespace resources {
template<typename T>
class UBO {
public:
    T data;
    GLuint handle;

    UBO(T data_) : data{data_} {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_UNIFORM_BUFFER, handle);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(T), &data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    void FullRefresh() {
        glBindBuffer(GL_UNIFORM_BUFFER, handle);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(T), &data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    // template<typename U, U T::* Member>
    // void PartialRefresh() {
        // glBindBuffer(GL_UNIFORM_BUFFER, handle);
        // glBufferSubData(GL_UNIFORM_BUFFER, offsetof(data, Member), sizeof(U), data.*Member);
    // }
    void Bind(GLint binding) {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, handle);
    }
};
}
}
