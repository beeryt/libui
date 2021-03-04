#pragma once

template <typename T = int16_t>
struct Rect {
  T x, y, w, h;
  bool operator==(const Rect& o) const {
    return x == o.x && y == o.y && w == o.w && h == o.h;
  }
  bool operator!=(const Rect& o) const { return !(*this == o); }
};
