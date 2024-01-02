// #include <bgfx/bgfx.h>
#include <filesystem>
#include <origami/resources/texture.hpp>
#include <fstream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/gl.h>


namespace origami {
namespace resources {
Texture::Texture(std::filesystem::path filePath, std::string type_) noexcept(false) : type {type_}, path {filePath} {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // some sanity checking
  if (!std::filesystem::exists(filePath)) {
    throw TextureCompilationError(filePath.string() + " does not exist!");
  }
  if (!std::filesystem::is_regular_file(filePath)) {
    throw TextureCompilationError(filePath.string() + " is not a regular file!");
  }
  int width, height, nrChannels;
  // stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
  uint8_t* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
  if (!data) {
    throw TextureCompilationError(filePath.string() + " did not load!");
  }

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  // FILE *file = fopen(filePath.c_str(), "rb");
  // fseek(file, 0, SEEK_END);
  // long fileSize = ftell(file);
  // fseek(file, 0, SEEK_SET);

  // const bgfx::Memory *mem = bgfx::alloc(fileSize + 1);
  // fread(mem->data, 1, fileSize, file);
  // mem->data[mem->size - 1] = '\0';
  // fclose(file);

  // handle = bgfx::createTexture(mem);
};

void Texture::Submit() {
  glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture() {
  // bgfx::destroy(handle);
}

TextureCompilationError::TextureCompilationError(std::string err_) : err {err_} {};

const char *TextureCompilationError::what() const noexcept {
  return err.c_str();
};
}
}
