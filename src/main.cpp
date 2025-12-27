// Now let's do something crazy my boi.
// Let's go and print a single pixel to the screen.
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "engine/rendering.hpp"
#include <algorithm>
#include <chrono>
#include <thread>
#include <type_traits>
#include <variant>
#include <vector>
int amount_rendered(std::vector<ENGObject> &objects) {
  int counter = 0;
  for ( auto &obj : objects) {
    std::visit([&counter] (auto &item) {
      if (item.draw) counter++;
    }, obj);
  }
  return counter;
}
int main() {
  App app;
  int w = 800;
  int h = 600;
  app.build(w, h, "Window name");
  int frame_w = 50;
  int frame_h = 50;
  for (int i = 0;i<w;i+=frame_w) {
    for (int j = 0;j<h;j+=frame_h) {
      ENGFrame r = ENGFrame(i, j, frame_w, frame_h, ENGBLACK);
      app.objects.push_back(r);
    }
  }
  int rendering_amount = amount_rendered(app.objects);
  std::string str = "Current rendering objects: " + std::to_string(rendering_amount);
  ENGText t = ENGText(0, 0, 20, str, ENGRED);
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
            item.x -= dx;
            item.y -= dy;
        }, obj);
      }
      gc = c;
    }else {
      gc.reset();
    }
    int rendering_amount = amount_rendered(app.objects);
    for ( auto &obj : app.objects) {
      std::visit([w, h, rendering_amount] (auto &item) {
          using T = std::decay_t<decltype(item)>;
          if constexpr (std::is_same_v<T, ENGFrame>) {
            if (((item.x > w && item.y > w) || (item.x > h && item.y > h))  && item.draw == true) {
              item.draw = false;
            } else if (((item.x < w && item.y < w) || (item.x < h && item.y < h))  && item.draw == false) {
              item.draw = true;
            }
          } else if constexpr (std::is_same_v<T, ENGText>) {
            std::string str = "Current rendering objects: " + std::to_string(rendering_amount);
            item.inside = str;
          }
      }, obj);
    }
    app.drawer.EngDrawAll(app.objects);

    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  return 0;
}
