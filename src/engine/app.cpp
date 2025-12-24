// The run method will every frame check the list of methods that should be
// on the screen.
//
// I am a genius.

#include "raylib.h"
#include "app.hpp"

App::App() = default;
bool App::build(const int sW, const int sH, const std::string &name) {
  screenName = name;
  screenHeight = sH;
  screenWidth = sW;
  InitWindow(sW, sH, name.c_str());
  if (!IsWindowReady()) {
    TraceLog(LOG_ERROR, "Failed to initialized a window.");
    return false;
  }
  SetTargetFPS(60);
  return true;
}
void App::EngBGColor(const EngColor c) {
  comms.push_back([this, c] () { BGColor(c); });
}
void App::BGColor(const EngColor c) {
  BeginDrawing();
  Color nc;
  nc.r = static_cast<unsigned char>(c.r * 255);
  nc.g = static_cast<unsigned char>(c.g * 255);
  nc.b = static_cast<unsigned char>(c.b * 255);
  nc.a = 255;
  ClearBackground(nc);
  EndDrawing();
}
void App::run() {
  while (!WindowShouldClose()) {
    for (auto &cmd : comms) {
      cmd();
    }
  }
  CloseWindow();
}
