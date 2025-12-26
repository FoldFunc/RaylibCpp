// The run method will every frame check the list of methods that should be
// on the screen.
//
// I am a genius.

#include "engine.hpp"
#include "raylib.h"
#include "rendering.hpp"
#include <functional>
#include <mutex>
#include <optional>
#include <variant>
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

std::optional<ENGRect*> App::find_player() {
  for (auto &obj : objects) {
    if (auto *player = std::get_if<ENGRect>(&obj)) {
      if (player->isPlayer) {
        return player;
      }
    }
  }
  return std::nullopt;
}
std::optional<ENGRect*> App::EngFindPlayer() {
  auto player = find_player();
  return player;
}
// This will set a variable that user will be able to get.
// That will happend every single frame.
// This design is so stupid that I'm not gonna even try to explain.
void App::EngGetUserInput() {
  submitAction(([this]() {getUserInput();}));
}

std::vector<ENGKeys> App::EngCurrentUserInputExtract() {
  std::vector<ENGKeys> ret;
  for ( ENGKeys key : keys_down ) {
    ret.push_back(key);
  }
  return ret;
}

bool App::KeysPressedContain(std::vector<ENGKeys> vk, ENGKeys k) {
  if (std::ranges::find(vk, k) != vk.end()) {
    return true;
  }
  return false;
}

void App::getUserInput() {
  keys_down.clear();
  if (IsKeyDown(KEY_D)) keys_down.insert(ENGKeys::D);
  if (IsKeyDown(KEY_Q)) keys_down.insert(ENGKeys::Q);
  if (IsKeyDown(KEY_ESCAPE)) keys_down.insert(ENGKeys::Escape);
  if (IsKeyDown(KEY_ENTER)) keys_down.insert(ENGKeys::Enter);
}
std::string App::to_string(ENGKeys key) {
  switch (key) {
    case ENGKeys::D: return "D";
    case ENGKeys::Q: return "q";
    case ENGKeys::Enter: return "ENTER";
    case ENGKeys::Escape: return "ESCAPE";
    case ENGKeys::WTF: return "WTF";
    default: return "Unknown";
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

