#ifndef ORIGAMI_INPUT_AXIS_HPP
#define ORIGAMI_INPUT_AXIS_HPP

#include <origami/graphics/window.hpp>

namespace origami::input {
class Axis {
public:
  virtual float Value(int dimension = 0) = 0;
  virtual ~Axis();
};
class KeyAxis : Axis {
  int keycode_positive, keycode_negative;
  graphics::Window* window_handle;
public:
  KeyAxis(int keycode_positive_, int keycode_negative_, graphics::Window* handle);
  virtual float Value(int dimension = 0) override;
  ~KeyAxis();
};
class MouseAxis : Axis {
  graphics::Window* handle;
public:
  MouseAxis(graphics::Window* handle);
  virtual float Value(int dimension) override;
  ~MouseAxis();
};
}

#endif // !ORIGAMI_INPUT_AXIS_HPP
