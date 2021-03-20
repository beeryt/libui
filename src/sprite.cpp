#include "sprite.h"

void Sprite::draw() {
  drawBitmapScaled(getGlobalPosition(), texture, scale);
}

void Sprite::setTexture(Bitmap texture) {
  if (this->texture != texture) {
    this->texture = texture;
    update();
  }
}

void Sprite::setScale(uint8_t scale) {
  if (scale == 0) while (1); // not suported
  if (this->scale != scale) {
    auto size = getSize() / this->scale; // get the existing size
    setSize(size * scale); // set the new size

    this->scale = scale;
    update();
  }
}

Bitmap Sprite::getTexture() const { return texture; }

void Sprite::setColor(Color color) { texture.setColor(color); update(); }
Color Sprite::getColor() const { return texture.getColor(); }