#pragma once
#include "basebutton.h"
#include "sprite.h"
#include "bitmap.h"

class TextureButton : public BaseButton {
  public:
    TextureButton(
      Node* parent = nullptr,
      Bitmap normal = {},
      Bitmap pressed = {},
      Bitmap disabled = {});
    TextureButton(
      Bitmap normal,
      Bitmap pressed = {},
      Bitmap disabled = {});

  protected:
    void modeChanged() override;

  private:
    Sprite sprite;
    Bitmap texture_normal;
    Bitmap texture_pressed;
    Bitmap texture_disabled;
};
