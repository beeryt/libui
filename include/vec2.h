#pragma once
#include <stdint.h>

template <typename T = int16_t>
struct Vec2 {
  T x = 0, y = 0;
  T dot() const;
  Vec2(T x = 0, T y = 0);

  // addition
  Vec2 operator+(const Vec2& rhs);
  Vec2& operator+=(const Vec2& rhs);

  // subtraction
  Vec2 operator-(const Vec2& rhs);
  Vec2& operator-=(const Vec2& rhs);

  // multiplication
  Vec2 operator*(const T& rhs) const;
  Vec2& operator*=(const T& rhs);

  // division
  Vec2 operator/(const int& rhs) const;
  Vec2& operator/=(const int& rhs);

  // equality
  bool operator!=(const Vec2& rhs) const;
  bool operator==(const Vec2& rhs) const;
};

