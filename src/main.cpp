// Now let's do something crazy my boi.
// Let's go and print a single pixel to the screen.
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "engine/rendering.hpp"
#include <algorithm>
#include <chrono>
#include <thread>
#include <variant>
#include <vector>
int main() {
  App app;
  app.build(800, 600, "Window name");
  ENGRect rect = ENGRect(200, 200, 20, 20, ENGBLACK); // This 'true' indicates this is a player.
  app.objects.push_back(rect);
  static std::optional<ENGCursorPosition> gc;
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
    app.drawer.EngDrawAll(app.objects);

    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  return 0;
}
