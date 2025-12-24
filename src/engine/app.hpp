#pragma once
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>


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


private:

  void BGColor(const EngColor c);

  int screenWidth = 0;
  int screenHeight = 0;
  std::string screenName;

  std::vector<std::function<void()>> comms;
  std::mutex comms_mutex;

};

