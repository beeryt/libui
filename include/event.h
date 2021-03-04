#pragma once
#include "vec2.hpp"

struct Event {
  enum Type { NONE, TOUCH, RELEASE };
  Type type;
  Vec2<> position;
};

