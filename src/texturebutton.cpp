#include "texturebutton.h"

TextureButton::TextureButton(Node* parent, Bitmap normal, Bitmap pressed, Bitmap disabled) :
  BaseButton(parent),
  texture_normal(normal),
  texture_pressed(pressed),
  texture_disabled(disabled) {
  addChild(sprite);
  sprite.setTexture(texture_normal);
}

TextureButton::TextureButton(Bitmap normal, Bitmap pressed, Bitmap disabled) :
  TextureButton(nullptr, normal, pressed, disabled) {}

void TextureButton::modeChanged() {
  Bitmap* ref = &texture_normal;
  switch (getMode()) {
  case ButtonMode::NORMAL: break;

  case ButtonMode::PRESSED:
    if (texture_pressed.isComplete()) { ref = &texture_pressed; }
    break;

  case ButtonMode::DISABLED:
    if (texture_disabled.isComplete()) { ref = &texture_disabled; }
    break;
  }
  sprite.setTexture(*ref);
}

