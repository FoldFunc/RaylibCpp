#include "rendering.hpp"
#include <raylib.h>
#include <type_traits>
#include <variant>
#include <vector>

Drawer::Drawer(std::function<void(ENGRenderCommand)> submitFn)
  : submit(std::move(submitFn)) {}
void Drawer::EngDrawPixel(ENGPixel p) {
  submit([this, p] () { // This shit depricated as hell
      draw_pixel(p);
  });
}
void Drawer::EngDrawRect(ENGRect r) {
  submit([this, r] () {
      draw_rect(r);
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
void Drawer::draw_rect(ENGRect r) {
  Color c;
  c.r = static_cast<unsigned char>(r.c.r*255);
  c.g = static_cast<unsigned char>(r.c.g*255);
  c.b = static_cast<unsigned char>(r.c.b*255);
  c.a = 255;
  DrawRectangle(r.x, r.y, r.w, r.h, c);
}
void Drawer::draw_pixel(ENGPixel p) {
  Color c;
  c.r = static_cast<unsigned char>(p.c.r*255);
  c.g = static_cast<unsigned char>(p.c.g*255);
  c.b = static_cast<unsigned char>(p.c.b*255);
  c.a = 255;
  DrawPixel(p.x, p.y, c);
}
void Drawer::EngDrawAll(std::vector<ENGObject> objects) {
  submit([this, objects] () {
      draw_all(objects);
  });
}
void Drawer::draw_all(std::vector<ENGObject> objects) {
  for (const auto &obj : objects) {
    std::visit([&](auto &&o) {
        using T = std::decay_t<decltype(o)>;
        if constexpr (std::is_same_v<T, ENGPixel>) {
          draw_pixel(o); 
        } else if constexpr (std::is_same_v<T, ENGRect>) {
          draw_rect(o); 
        }
    }, obj);
  }
}
