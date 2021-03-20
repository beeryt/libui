#pragma once
#include "canvas.h"
#include "bitmap.h"

class Sprite : public Canvas {
  public:
    using Canvas::Canvas;
    void draw() override;

    void setTexture(Bitmap texture);
    Bitmap getTexture() const;

    void setScale(uint8_t scale);
    uint8_t getScale() const;

    void setColor(Color color);
    Color getColor() const;

  private:
    Bitmap texture;
    uint8_t scale = 1;
};

