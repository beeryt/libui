#pragma once
#include "canvas.h"
#include "marquee.h"
#include "playback.h"

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

