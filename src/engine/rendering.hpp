#pragma once
#include "engine.hpp"
#include <functional>
struct ENGPixel {
  int x;
  int y;
  EngColor c;
};
class Drawer {
public:
  explicit Drawer(std::function<void(ENGRenderCommand)> submitFn);

  void EngDrawPixel(ENGPixel p);
  void draw_pixel(ENGPixel p);

  void EngBGColor(const EngColor c);
  void BGColor(const EngColor c);

private:
  std::function<void(ENGRenderCommand)> submit;
};
