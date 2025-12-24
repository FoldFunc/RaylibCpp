#include "engine/app.hpp"
#include <iostream>
int main() {
  App app;
  app.build(100, 100, "Window name");
  while (app.is_running()) {
    app.EngGetUserInput(); // This mf sets a variable that we have to get from another method.
    char current_input = app.EngCurrentUserInputExtract();
    std::cout << "Current char pressed: " << current_input << "\n";
    app.EngBGColor(ENGWHITE);
    app.run_frame();
  }
  return 0;
}
