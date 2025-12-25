#pragma once
#include <functional>
#include <mutex>
#include <string>
#include <vector>

enum class ENGKeys {
  None,
  Enter,
  Escape,
  Q,
  WTF,
};

struct EngColor {
  float r, g, b;
};

constexpr EngColor ENGWHITE = {1.0f, 1.0f, 1.0f};
constexpr EngColor ENGBLACK = {0.0f, 0.0f, 0.0f};

class App {

public:
  App();

  bool build(const int sW, const int sH, const std::string &name);
  void stop();
  void run_frame();

  bool is_running();

  void EngBGColor(const EngColor c);
  void EngGetUserInput();
  ENGKeys EngCurrentUserInputExtract();
private:

  void BGColor(const EngColor c);
  void getUserInput();

  int screenWidth = 0;
  int screenHeight = 0;
  std::string screenName;


  ENGKeys current_user_input = ENGKeys::None;

  std::vector<std::function<void()>> comms;
  std::mutex comms_mutex;

};

