// Now let's do something crazy my boi.
// Let's go and print a single pixel to the screen.
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "engine/rendering.hpp"
#include <chrono>
#include <thread>
#include <vector>
int main() {
  App app;
  app.build(800, 600, "Window name");
  ENGRect rect = ENGRect(200, 200, 20, 20, ENGBLACK); // This 'true' indicates this is a player.
  ENGLine line = ENGLine(200, 200, 300, 300, ENGBLACK);
  ENGCircle circle = ENGCircle(400, 400, 20, ENGBLACK);
  std::string hello = "Hello world";
  ENGText text = ENGText(100, 100, 20, hello, ENGBLACK);
  app.objects.push_back(rect);
  app.objects.push_back(line);
  app.objects.push_back(circle);
  app.objects.push_back(text);
  while (app.is_running()) {
    app.drawer.EngBGColor(ENGWHITE);

    app.EngGetUserInput(); // This mf sets a variable that we have to get from another method.
    std::vector<ENGKeys> current_input = app.EngCurrentUserInputExtract();


    app.drawer.EngDrawAll(app.objects);

    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  return 0;
}
