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
void App::run() {
  while (!WindowShouldClose()) {
    continue;
  }

  CloseWindow();
}
