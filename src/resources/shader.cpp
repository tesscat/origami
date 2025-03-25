#include "glad/gl.h"
#include <origami/resources/shader.hpp>
#include <fstream>
#include <vector>
#include <origami/log.hpp>
#include <utility>


namespace origami {
namespace resources {
Shader::Shader(std::filesystem::path filePath, GLenum shaderType) noexcept(false) {
    // some sanity checking
    if (!std::filesystem::exists(filePath)) {
        throw ShaderCompilationError(filePath.string() + " does not exist!");
    }
    if (!std::filesystem::is_regular_file(filePath)) {
        throw ShaderCompilationError(filePath.string() + " is not a regular file!");
    }

    shader = glCreateShader(shaderType);

    std::ifstream file;
    file.open(filePath);
    file.seekg(0, std::ios_base::end); // Seek to end of file.
    const unsigned int file_length = file.tellg();
    file.seekg(0);
    std::vector<char> file_data(file_length);
    file.read(&file_data[0], file_length);

    char* d1 = file_data.data();
    const std::string data = std::string(d1);
    const char* const s = data.c_str();

    glShaderSource(shader, 1, &s, NULL);
    glCompileShader(shader);

    file.close();

    int success;
    char infoLog[4096];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderInfoLog(shader, 4096, NULL, infoLog);
    if(!success) {
        // printf(s);
        throw ShaderCompilationError(filePath.string() + ": " + infoLog);
    }
    if (infoLog[0]) {
       WARN("Shader warnings for {}:\n{}", filePath.string(), infoLog); 
    }
};


VertexShader::VertexShader(std::filesystem::path filePath) noexcept(false) : Shader(filePath, GL_VERTEX_SHADER) {
    // some sanity checking
    /*
    if (!std::filesystem::exists(filePath)) {
        throw ShaderCompilationError(filePath.string() + " does not exist!");
    }
    if (!std::filesystem::is_regular_file(filePath)) {
        throw ShaderCompilationError(filePath.string() + " is not a regular file!");
    }

    shader = glCreateShader(GL_VERTEX_SHADER);

    std::ifstream file;
    file.open(filePath);
    file.seekg(0, std::ios_base::end); // Seek to end of file.
    const unsigned int file_length = file.tellg();
    file.seekg(0);
    std::vector<char> file_data(file_length);
    file.read(&file_data[0], file_length);

    char* d1 = file_data.data();
    const std::string data = std::string(d1);
    const char* const s = data.c_str();

    glShaderSource(shader, 1, &s, NULL);
    glCompileShader(shader);

    file.close();

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw ShaderCompilationError(filePath.string() + ": " + infoLog);
    } */
};

// TODO: dedup logic

VertexShader::~VertexShader() {
}

FragmentShader::FragmentShader(std::filesystem::path filePath) noexcept(false) : Shader(filePath, GL_FRAGMENT_SHADER) {}

FragmentShader::~FragmentShader() {
}

ComputeShader2D::ComputeShader2D(std::filesystem::path filePath, unsigned int x_, unsigned int y_) noexcept(false) : Shader(filePath, GL_COMPUTE_SHADER), x{x_}, y{y_} {
    // Also create a separate program so I can run this independently
    program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);
    // check for errors
    int success;
    char infoLog[4096];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramInfoLog(program, 4096, NULL, infoLog);
    if(!success) {
        throw resources::ShaderCompilationError(std::string("program error: ") + infoLog);
    }
    if (infoLog[0]) {
       WARN("Shader warnings for {}:\n{}", filePath.string(), infoLog); 
    }
    // also construct a texture
    glGenTextures(1, &texOutput);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texOutput);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, x, y, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindImageTexture(0, texOutput, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
}

ComputeShader2D::~ComputeShader2D() {
}

void ComputeShader2D::Dispatch() {
    glUseProgram(program);
    glDispatchCompute((GLuint)x, (GLuint)y, 1);
}

void ComputeShader2D::Await() {
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void ComputeShader2D::Submit(components::Program program_) {
    program_.Submit();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texOutput);
    // TODO: bind relevant size uniforms, maybe??
}

GLint ComputeShader2D::GetUniformLocation(const char* uniform) {
    return glGetUniformLocation(program, uniform);
}

ShaderCompilationError::ShaderCompilationError(std::string err_) : err {err_} {};

const char *ShaderCompilationError::what() const noexcept {
    return err.c_str();
};

std::string ShaderPathPrefix() {
    return "shaders/glsl/";
}
} // namespace resources
}
