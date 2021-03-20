#pragma once
#include "canvas.h"
#include "marquee.h"
#include "playback.h"
#include "texturebutton.h"
#include "sprite.h"
#include "util.h"
#include "song.h"
#include <vector>

Bitmap loadBitmap(const char*);

extern Bitmap play_texture;
extern Bitmap pause_texture;
extern Bitmap next_texture;
extern Bitmap prev_texture;
extern Bitmap art_texture;

class Controls : public Canvas {
public:
  TextureButton prev, play, next;
  Controls();
  void refreshLayout();
};

class MP3 : public Canvas {
  public:
    MP3(short x, short y);
    void refreshLayout();

    Marquee title;
    Marquee artist;
    Marquee album;
    Sprite art;
    Playback playback;
    Controls controls;
};

