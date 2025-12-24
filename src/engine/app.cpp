// The run method will every frame check the list of methods that should be
// on the screen.
//
// I am a genius.

#include "raylib.h"
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>
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

bool App::is_running() {
  return !WindowShouldClose();
}

void App::EngBGColor(const EngColor c) {
  std::lock_guard<std::mutex> lock(comms_mutex);
  comms.push_back([this, c] () { BGColor(c); });
}
// This will set a variable that user will be able to get.
// That will happend every single frame.
// This design is so stupid that I'm not gonna even try to explain.
void App::EngGetUserInput() {
  std::lock_guard<std::mutex> lock(comms_mutex);
  comms.push_back([this] () { getUserInput(); });
}

char App::EngCurrentUserInputExtract() {
  return current_user_input;
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

void App::getUserInput() {
  int key = GetCharPressed();
  char c = static_cast<char>(key);
  current_user_input = c;
}

void App::run_frame() {
  std::vector<std::function<void()>> currnetComms;
  {
    std::lock_guard<std::mutex> lock(comms_mutex);
    currnetComms.swap(comms);
  }
  for (auto &cmd : currnetComms) {
    cmd();
  }
}

