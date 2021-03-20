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
  return Vec2{
    static_cast<T>(this->x + rhs.x),
    static_cast<T>(this->y + rhs.y)
  };
}

template <typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& rhs) {
  return Vec2<T>{
    static_cast<T>(this->x - rhs.x),
    static_cast<T>(this->y - rhs.y)
  };
}

template <typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& rhs) {
  this->x -= rhs.x;
  this->y -= rhs.y;
  return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator/(const int& rhs) const {
  return Vec2<T>{
    static_cast<T>(this->x / rhs),
    static_cast<T>(this->y / rhs)
  };
}

template <typename T>
Vec2<T> Vec2<T>::operator*(const T& rhs) const {
  return Vec2<T>{
    static_cast<T>(this->x * rhs),
    static_cast<T>(this->y * rhs)
  };
}

template <typename T>
Vec2<T>& Vec2<T>::operator/=(const int& rhs) {
  this->x /= rhs;
  this->y /= rhs;
  return *this;
}

