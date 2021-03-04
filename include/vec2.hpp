#include "vec2.h"
#pragma once

template <typename T>
Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

template <typename T>
T Vec2<T>::dot() const { return x * y; }

template <typename T>
bool Vec2<T>::operator==(const Vec2<T>& rhs) const { return this->x == rhs.x && this->y == rhs.y; }

template <typename T>
bool Vec2<T>::operator!=(const Vec2<T>& rhs) const { return !(*this == rhs);  }

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& rhs) {
  return Vec2{ this->x + rhs.x, this->y + rhs.y };
}

template <typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}

