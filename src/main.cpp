// Now let's do something crazy my boi.
// Let's go and print a single pixel to the screen.
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include <chrono>
#include <thread>
int main() {
  App app;
  app.build(100, 100, "Window name");
  ENGPixel pixel = ENGPixel(100, 100, ENGBLACK);
  while (app.is_running()) {
    app.drawer.EngBGColor(ENGWHITE);
    app.EngGetUserInput(); // This mf sets a variable that we have to get from another method.
    ENGKeys current_input = app.EngCurrentUserInputExtract();
    if (current_input == ENGKeys::Escape) {
      app.stop();
    }
    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  return 0;
}
