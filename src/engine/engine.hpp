#pragma once

#include <functional>
using ENGRenderCommand = std::function<void()>;

enum class ENGKeys {
  LMB,
  RMB,
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
  auto operator<=>(const EngColor&) const = default;
};

constexpr EngColor ENGWHITE   = {1.0f, 1.0f, 1.0f};
constexpr EngColor ENGBLACK   = {0.0f, 0.0f, 0.0f};
constexpr EngColor ENGRED     = {1.0f, 0.0f, 0.0f};
constexpr EngColor ENGBLUE    = {0.0f, 0.0f, 1.0f};
constexpr EngColor ENGGREEN   = {0.0f, 1.0f, 0.0f};
constexpr EngColor ENGMAGENTA = {1.0f, 0.0f, 1.0f};

constexpr EngColor ENGGRAY    = {128.0f/255.0f, 128.0f/255.0f, 128.0f/255.0f};
constexpr EngColor ENGGRASS   = {76.0f/255.0f, 175.0f/255.0f, 80.0f/255.0f};
constexpr EngColor ENGSAND    = {237.0f/255.0f, 201.0f/255.0f, 175.0f/255.0f};
constexpr EngColor ENGWATER   = {64.0f/255.0f, 164.0f/255.0f, 223.0f/255.0f};
