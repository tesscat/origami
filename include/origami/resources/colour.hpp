#ifndef ORIGAMI_RESOURCES_COLOUR_HPP
#define ORIGAMI_RESOURCES_COLOUR_HPP

#include <cstdint>

namespace origami::resources {
struct ColourBGRA32 {
  uint8_t blue;
  uint8_t green;
  uint8_t red;
  uint8_t alpha;
} __attribute__((__packed__));


}

#endif // !ORIGAMI_RESOURCES_COLOUR_HPP
