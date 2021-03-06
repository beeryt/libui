#include "playback.h"
#include <assert.h>

// TODO: these numbers should consider the text size
static const int16_t padv = 1;
static const int16_t padh = 6;

Playback::Playback(Node* parent, int duration)
  : Canvas(parent), progress(0), duration(duration) {
  slider.setMin(0);
  slider.setVal(0);
  slider.setMax(duration);
  addChild(this->progress);
  addChild(this->slider);
  addChild(this->duration);
}

void Playback::draw() {
  int16_t x, y, width;

  auto textSize = this->progress.getSize();
  assert(textSize == this->duration.getSize());

  width = getSize().x;

  // set progress position
  x = padh;
  y = 0;
  this->progress.setPosition({x,y});

  // set slider position
  x += textSize.x + padh;
  y = padv;
  this->slider.setPosition({x,y});

  // set slider size
  x = width - 2*textSize.x - 4*padh;
  y = 7 - 2*padv; // 7 is used instead of 8 since text is 5x7 with 1px padding
  this->slider.setSize({x,y});

  // set duration position
  x += this->slider.getPosition().x + padh;
  y = 0;
  this->duration.setPosition({x,y});
}

Playback::Playback(int duration) : Playback(NULL, duration) {}
void Playback::setProgress(int value) {
  this->progress.setTime(value);
  slider.setVal(value);
}

void Playback::setDuration(int value) {
  duration.setTime(value);
  slider.setMax(value);
  slider.setVal(progress.getTime());
}

int Playback::getProgress() const {
  return progress.getTime();
}

int Playback::getDuration() const {
  return duration.getTime();
}
