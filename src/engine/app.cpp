// The run method will every frame check the list of methods that should be
// on the screen.
//
// I am a genius.

#include "raylib.h"
#include <functional>
#include <mutex>
#include <vector>
#include "app.hpp"

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
bool App::is_running() {
  return !WindowShouldClose();
}
void App::stop() {
  CloseWindow();
}

void App::submitAction(ENGRenderCommand cmd) {
  std::lock_guard<std::mutex> lock(comms_mutex);
  comms.push_back(std::move(cmd));
}

// This will set a variable that user will be able to get.
// That will happend every single frame.
// This design is so stupid that I'm not gonna even try to explain.
void App::EngGetUserInput() {
  submitAction(([this]() {getUserInput();}));
}

ENGKeys App::EngCurrentUserInputExtract() {
  return current_user_input;
}


void App::getUserInput() {
  current_user_input = ENGKeys::None;
  if (IsKeyPressed(KEY_ENTER)) {
    current_user_input = ENGKeys::Enter;
  } else if (IsKeyPressed(KEY_ESCAPE)) {
    current_user_input = ENGKeys::Escape;
  } else if (IsKeyPressed(KEY_Q)) {
    current_user_input = ENGKeys::Q;
  } else {
    current_user_input = ENGKeys::WTF;
  }
}

void App::run_frame() {
  BeginDrawing();
  std::vector<std::function<void()>> currnetComms;
  {
    std::lock_guard<std::mutex> lock(comms_mutex);
    currnetComms.swap(comms);
  }
  for (auto &cmd : currnetComms) {
    cmd();
  }
  EndDrawing();
}

