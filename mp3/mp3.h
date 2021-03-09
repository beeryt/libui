#pragma once
#include "canvas.h"
#include "marquee.h"
#include "playback.h"
#include "texturebutton.h"

template <typename T>
T ntoh(T raw) {
  uint8_t* data = reinterpret_cast<uint8_t*>(&raw);
  T out = 0;
  int size = sizeof(T);
  for (int i = 0; i < size; ++i) {
    out |= ((T)data[size-i-1] << (i*8));
  }
  return out;
}

Bitmap loadBitmap(const char*);

extern Bitmap play_texture;
extern Bitmap pause_texture;
extern Bitmap next_texture;
extern Bitmap prev_texture;

class MP3 : public Canvas {
  public:
    MP3(short x, short y);
    void refreshLayout();

    Marquee title;
    Marquee artist;
    Playback playback;
    Canvas controls;
};

