// Now let's do something crazy my boi.
// Let's go and print a single pixel to the screen.
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "engine/rendering.hpp"
#include <chrono>
#include <thread>
#include <vector>
void player_move(App &app, const std::vector<ENGKeys> &input, ENGRect *player) {
  if (app.KeysPressedContain(input, ENGKeys::D) && player) player->x += 10;
  if (app.KeysPressedContain(input, ENGKeys::A) && player) player->x -= 10;
  if (app.KeysPressedContain(input, ENGKeys::S) && player) player->y += 10;
  if (app.KeysPressedContain(input, ENGKeys::W) && player) player->y -= 10;
  else {
    return;
  }
}
int main() {
  App app;
  app.build(800, 600, "Window name");
  ENGRect rect = ENGRect(200, 200, 20, 20, ENGBLACK, true); // This 'true' indicates this is a player.
  app.objects.push_back(rect);
  ENGRect *player = nullptr;
  if (auto player_i = app.EngFindPlayer()) {
    player = (*player_i);
  }
  while (app.is_running()) {
    app.drawer.EngBGColor(ENGWHITE);

    app.EngGetUserInput(); // This mf sets a variable that we have to get from another method.
    std::vector<ENGKeys> current_input = app.EngCurrentUserInputExtract();

    player_move(app, current_input, player);

    app.drawer.EngDrawAll(app.objects);

    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  return 0;
}
