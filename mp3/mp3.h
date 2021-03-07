#pragma once
#include "canvas.h"
#include "playback.h"

extern Canvas ui;

class MP3 : public Canvas {
  public:
    MP3(short x, short y);
    void refreshLayout();

    Text title;
    Text artist;
    Playback playback;
    Canvas controls;
};

