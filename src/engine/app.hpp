#pragma once
#include <string>
class App {
public:
  App();

  bool build(const int sW, const int sH, const std::string &name);
  void run();
private:
  int screenWidth = 0;
  int screenHeight = 0;
  std::string screenName;
};
