#pragma once
#include "canvas.h"
#include "bitmap.h"

class Sprite : public Canvas {
  public:
    using Canvas::Canvas;
    void draw() override;

    void setTexture(Bitmap texture);
    Bitmap getTexture() const;

  private:
    Bitmap texture;
};

