#include "rendering.hpp"
#include <raylib.h>
#include <type_traits>
#include <variant>
#include <vector>

Drawer::Drawer(std::function<void(ENGRenderCommand)> submitFn)
  : submit(std::move(submitFn)) {}

void Drawer::EngDrawText(ENGText t) {
  submit([this, t] () {
      draw_text(t);
  });
}

void Drawer::EngDrawPixel(ENGPixel p) {
  submit([this, p] () { // This shit depricated as hell
      draw_pixel(p);
  });
}
void Drawer::EngDrawCircle(ENGCircle c) {
  submit([this, c] (){
      draw_circle(c);
  });
}
void Drawer::EngDrawRect(ENGRect r) {
  submit([this, r] () {
      draw_rect(r);
  });
}

void Drawer::EngDrawFrame(ENGFrame f) {
  submit([this, f] () {
      draw_frame(f);
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

void Drawer::draw_text(ENGText t) {
  Color nc;
  nc.r = static_cast<unsigned char>(t.c.r * 255);
  nc.g = static_cast<unsigned char>(t.c.g * 255);
  nc.b = static_cast<unsigned char>(t.c.b * 255);
  nc.a = 255;
  DrawText(t.inside.c_str(), t.x, t.y, t.s, nc);
}

void Drawer::draw_circle(ENGCircle c) {
  Color cn;
  cn.r = static_cast<unsigned char>(c.c.r*255);
  cn.g = static_cast<unsigned char>(c.c.g*255);
  cn.b = static_cast<unsigned char>(c.c.b*255);
  cn.a = 255;
  DrawCircle(c.x, c.y, c.r, cn);
}

void Drawer::draw_rect(ENGRect r) {
  Color c;
  c.r = static_cast<unsigned char>(r.c.r*255);
  c.g = static_cast<unsigned char>(r.c.g*255);
  c.b = static_cast<unsigned char>(r.c.b*255);
  c.a = 255;
  DrawRectangle(r.x, r.y, r.w, r.h, c);
}

void Drawer::draw_frame(ENGFrame f) {
  Color c;
  c.r = static_cast<unsigned char>(f.c.r*255);
  c.g = static_cast<unsigned char>(f.c.g*255);
  c.b = static_cast<unsigned char>(f.c.b*255);
  c.a = 255;
  DrawRectangleLines(f.x, f.y, f.w, f.h, c);
}

void Drawer::draw_pixel(ENGPixel p) {
  Color c;
  c.r = static_cast<unsigned char>(p.c.r*255);
  c.g = static_cast<unsigned char>(p.c.g*255);
  c.b = static_cast<unsigned char>(p.c.b*255);
  c.a = 255;
  DrawPixel(p.x, p.y, c);
}

void Drawer::draw_line(ENGLine l) {
  Color c;
  c.r = static_cast<unsigned char>(l.c.r*255);
  c.g = static_cast<unsigned char>(l.c.g*255);
  c.b = static_cast<unsigned char>(l.c.b*255);
  c.a = 255;
  DrawLine(l.x, l.y, l.ex, l.ey, c);
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
          if (o.draw) {
            draw_pixel(o); 
          }
        } else if constexpr (std::is_same_v<T, ENGRect>) {
          if (o.draw) {
            draw_rect(o); 
          }
        } else if constexpr (std::is_same_v<T, ENGLine>) {
          if (o.draw) {
            draw_line(o); 
          }
        } else if constexpr (std::is_same_v<T, ENGCircle>) {
          if (o.draw) {
            draw_circle(o); 
          }
        } else if constexpr (std::is_same_v<T, ENGText>) {
          if (o.draw) {
            draw_text(o); 
          }
        } else if constexpr (std::is_same_v<T, ENGFrame>) {
          if (o.draw) {
            draw_frame(o); 
          }
        }
    }, obj);
  }
}
