/*
 * Ok now my task is to create a world that will
 * generate as I am moving my mouse over the screen.
 */
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "engine/rendering.hpp"
#include <algorithm>
#include <chrono>
#include <thread>
#include <type_traits>
#include <variant>
#include <vector>
int main() {
  App app;
  int w = 800;
  int h = 600;
  app.build(w, h, "Window name");
  int frame_w = 50;
  int frame_h = 50;
  for (int i = 0;i<w;i+=frame_w) {
    for (int j = 0;j<h;j+=frame_h) {
      ENGFrame r{
        .x = i,
        .y = j,
        .w = frame_w,
        .h = frame_h,
        .c = ENGBLACK,
        .id = 1,
      };
      app.objects.push_back(r);
    }
  }
  int rendering_amount = app.amount_rendered();
  std::string str = "Current rendering objects: " + std::to_string(rendering_amount);
  ENGText t{
    .x = 0,
      .y = 0,
      .s = 20,
      .inside = str,
      .c = ENGRED,
      .sticky = true,
      .id = 2,
  };
  static std::optional<ENGCursorPosition> gc;
  app.objects.push_back(t);
  while (app.is_running()) {
    app.drawer.EngBGColor(ENGWHITE);

    app.EngGetUserInput(); // This mf sets a variable that we have to get from another method.
    std::vector<ENGKeys> current_input = app.EngCurrentUserInputExtract();

    if (std::ranges::find(current_input, ENGKeys::LMB) != current_input.end()) {
      ENGCursorPosition c = app.EngGetCursorPosition();
      if (!gc) {
        gc = c;
        continue;
      }
      int dx = c.x - gc->x;
      int dy = c.y - gc->y;
      for (auto &obj : app.objects) {
        std::visit([dx, dy] (auto &item) {
            if (!item.sticky) {
            item.x += dx;
            item.y += dy;
            }
            }, obj);
      }
      gc = c;
    }else {
      gc.reset();
    }
    int rendering_amount = app.amount_rendered();
    for ( auto &obj : app.objects) {
      std::visit([w, h, rendering_amount] (auto &item) {
          using T = std::decay_t<decltype(item)>;
          if constexpr (std::is_same_v<T, ENGFrame>) {
            if (item.id == 1) {
              if (item.x + item.w < 0 || item.y + item.h < 0 || item.x > w || item.y > h) {
                item.draw = false;
              } else {
                item.draw = true;
              }
            }
          } else if constexpr (std::is_same_v<T, ENGText>) {
              item.inside = "Current rendering objects: " + std::to_string(rendering_amount);
          }
        }, obj);
    }
    app.drawer.EngDrawAll(app.objects);

    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  return 0;
}
