// You need to pass all of the arguments before run
// Need to fix this shit.
// So you can change behaviour
#include "engine/app.hpp"
int main() {
  App app;
  app.build(100, 100, "Window name");
  app.BGColor(ENGWHITE);
  app.run();
  return 0;
}
