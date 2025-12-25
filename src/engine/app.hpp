#pragma once
#include <functional>
#include <mutex>
#include <string>
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

  bool is_running();

  void EngGetUserInput();
  ENGKeys EngCurrentUserInputExtract();

  Drawer drawer;

private:

  void getUserInput();

  int screenWidth = 0;
  int screenHeight = 0;
  std::string screenName;

  std::vector<ENGRenderCommand> comms;
  std::mutex comms_mutex;


  ENGKeys current_user_input = ENGKeys::None;
};

