#pragma once
#include <functional>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>
#include "rendering.hpp"
#include "engine.hpp"

class App {
public:
  App()
    : drawer([this] (ENGRenderCommand cmd) { submitAction(std::move(cmd)); }) {}

  bool build(const int sW, const int sH, const std::string &name);
  void stop();
  void run_frame();
  void submitAction(ENGRenderCommand cmd);
  std::string to_string(ENGKeys key);

  bool is_running();

  void EngGetUserInput();
  std::vector<ENGKeys> EngCurrentUserInputExtract();

  std::optional<ENGRect*> EngFindPlayer();
  std::optional<ENGRect*>find_player();

  bool KeysPressedContain(std::vector<ENGKeys> vk, ENGKeys k);

  Drawer drawer;
  std::unordered_set<ENGKeys> keys_down;
  std::vector<ENGObject> objects;
private:

  void getUserInput();

  int screenWidth = 0;
  int screenHeight = 0;
  std::string screenName;

  std::vector<ENGRenderCommand> comms;
  std::mutex comms_mutex;


  ENGKeys current_user_input = ENGKeys::None;
};

