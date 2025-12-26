#pragma once
#include "engine.hpp"
#include <functional>
#include <variant>
#include <vector>

struct ENGRect {
  int x;
  int y;
  int w;
  int h;
  EngColor c;
  bool isPlayer;
};

struct ENGPixel {
  int x;
  int y;
  EngColor c;
};
using ENGObject = std::variant<ENGPixel, ENGRect>;

class Drawer {
public:
  explicit Drawer(std::function<void(ENGRenderCommand)> submitFn);

  void EngDrawAll(std::vector<ENGObject> objects);
  void draw_all(std::vector<ENGObject> objects);

  void EngDrawPixel(ENGPixel p);
  void draw_pixel(ENGPixel p);

  void EngDrawRect(ENGRect r);
  void draw_rect(ENGRect p);

  void EngBGColor(const EngColor c);
  void BGColor(const EngColor c);

private:
  std::function<void(ENGRenderCommand)> submit;
};
