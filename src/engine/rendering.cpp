#include "rendering.hpp"
#include <raylib.h>

Drawer::Drawer(std::function<void(ENGRenderCommand)> submitFn)
  : submit(std::move(submitFn)) {}
void Drawer::EngDrawPixel(ENGPixel p) {
  submit([this, p] () { // This shit depricated as hell
      draw_pixel(p);
  });
}
void Drawer::EngBGColor(const EngColor c) {
  submit(([this, c] () {BGColor(c);}));
}
void Drawer::BGColor(const EngColor c) {
  Color nc;
  nc.r = static_cast<unsigned char>(c.r * 255);
  nc.g = static_cast<unsigned char>(c.g * 255);
  nc.b = static_cast<unsigned char>(c.b * 255);
  nc.a = 255;
  ClearBackground(nc);
}
void Drawer::draw_pixel(ENGPixel p) {
  Color c;
  c.r = static_cast<unsigned char>(p.c.r*255);
  c.g = static_cast<unsigned char>(p.c.g*255);
  c.b = static_cast<unsigned char>(p.c.b*255);
  c.a = 255;
  DrawPixel(p.x, p.y, c);
}
