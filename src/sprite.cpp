#include "sprite.h"

void Sprite::draw() {
  drawBitmap(getGlobalPosition(), texture);
}

void Sprite::setTexture(Bitmap texture) {
  if (this->texture != texture) {
    this->texture = texture;
    update();
  }
}

Bitmap Sprite::getTexture() const { return texture; }