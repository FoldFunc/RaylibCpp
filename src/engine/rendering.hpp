#pragma once
#include "engine.hpp"
#include <functional>
#include <string>
#include <variant>
#include <vector>


struct ENGText {
  int x;
  int y;
  int s;
  std::string inside;
  EngColor c = ENGWHITE;
};

struct ENGCircle {
  int x;
  int y;
  int r;
  EngColor c = ENGWHITE;
  bool isPlayer = false;
};

struct ENGRect {
  int x;
  int y;
  int w;
  int h;
  EngColor c = ENGWHITE;
  bool isPlayer = false;
};

struct ENGLine {
  int x;
  int y;
  int ex;
  int ey;
  EngColor c;
};

struct ENGPixel {
  int x;
  int y;
  EngColor c;
};
using ENGObject = std::variant<ENGPixel, ENGRect, ENGLine, ENGCircle, ENGText>;

class Drawer {
public:
  explicit Drawer(std::function<void(ENGRenderCommand)> submitFn);

  void EngDrawAll(std::vector<ENGObject> objects);
  void draw_all(std::vector<ENGObject> objects);

  void EngDrawText(ENGText t);
  void draw_text(ENGText t);

  void EngDrawPixel(ENGPixel p);
  void draw_pixel(ENGPixel p);

  void EngDrawCircle(ENGCircle c);
  void draw_circle(ENGCircle c);

  void EngDrawRect(ENGRect r);
  void draw_rect(ENGRect p);

  void EngDrawLine(ENGLine l);
  void draw_line(ENGLine l);

  void EngBGColor(const EngColor c);
  void BGColor(const EngColor c);

private:
  std::function<void(ENGRenderCommand)> submit;
};
