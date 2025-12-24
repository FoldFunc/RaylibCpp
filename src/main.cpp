#include "engine/app.hpp"
int main() {
  App app;
  app.build(100, 100, "Window name");
  app.run();
  return 0;
}
