// Now let's do something crazy my boi.
// Let's go and print a single pixel to the screen.
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "engine/rendering.hpp"
#include <chrono>
#include <thread>
#include <vector>
void player_move(App &app, const std::vector<ENGKeys> &input) {
  if (!app.KeysPressedContain(input, ENGKeys::D)) {
    return;
  }
  if (auto player = app.EngFindPlayer()) {
    (*player)-> x+= 10;
  }
}
int main() {
  App app;
  app.build(800, 600, "Window name");
  ENGRect rect = ENGRect(200, 200, 20, 20, ENGBLACK, true);
  app.objects.push_back(rect);
  while (app.is_running()) {
    app.drawer.EngBGColor(ENGWHITE);

    app.EngGetUserInput(); // This mf sets a variable that we have to get from another method.
    std::vector<ENGKeys> current_input = app.EngCurrentUserInputExtract();

    player_move(app, current_input);

    app.drawer.EngDrawAll(app.objects);

    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  return 0;
}
