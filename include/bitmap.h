#pragma once
#include "vec2.hpp"
#include "color.h"
#include <cstddef>
#include <cstdint>

class Bitmap {
  public:
    Bitmap();
    Bitmap(const uint8_t *bitmap, size_t w, size_t h);
    Bitmap(const uint8_t *bitmap, Vec2<size_t> size);

    bool operator==(const Bitmap& rhs) const;
    bool operator!=(const Bitmap& rhs) const;

    bool isComplete() const;

    void setBitmap(const uint8_t *bitmap, size_t w, size_t h);
    void setBitmap(const uint8_t *bitmap, Vec2<size_t> size);
    const uint8_t* getBitmap(size_t *w, size_t *h) const;
    const uint8_t* getBitmap(Vec2<size_t> *size) const;
    const uint8_t* getBitmap() const;

    Vec2<size_t> getSize() const;

    void setColor(Color color) { this->color = color; }
    Color getColor() const { return color; }

    void setBackground(Color color) { this->background = color; }
    Color getBackground() const { return background; }

  private:
    const uint8_t *bitmap;
    Vec2<size_t> size;
    Color color = Colors::white;
    Color background = Colors::black;
};
