#pragma once
#include <functional>
#include <string>
#include <vector>


struct EngColor {
  float r, g, b;
};

constexpr EngColor ENGWHITE = {1.0f, 1.0f, 1.0f};

class App {

public:
  App();

  bool build(const int sW, const int sH, const std::string &name);
  void run();

  void EngBGColor(const EngColor c);
  void BGColor(const EngColor c);


private:
  int screenWidth = 0;
  int screenHeight = 0;
  std::string screenName;

  std::vector<std::function<void()>> comms;

};

