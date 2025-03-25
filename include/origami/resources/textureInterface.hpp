#ifndef ORIGAMI_RESOURCES_TEXTURE_INTERFACE_HPP
#define ORIGAMI_RESOURCES_TEXTURE_INTERFACE_HPP

#include "origami/components/program.hpp"
namespace origami::resources {

class TextureInterface {
public:
  virtual ~TextureInterface() {};

  virtual void Submit(components::Program program) =0;
};
}
#endif // !ORIGAMI_RESOURCES_TEXTURE_INTERFACE_HPP
