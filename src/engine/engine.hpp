#pragma once

#include <functional>
using ENGRenderCommand = std::function<void()>;

enum class ENGKeys {
  Enter,
  Escape,
  Q,
  W,
  S,
  A,
  D,
  WTF,
  None,
};

struct EngColor {
  float r, g, b;
};

constexpr EngColor ENGWHITE = {1.0f, 1.0f, 1.0f};
constexpr EngColor ENGBLACK = {0.0f, 0.0f, 0.0f};

