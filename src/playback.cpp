#include "playback.h"
#include <assert.h>

static const int16_t padv = 2;
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
  int16_t x, y, width = getSize().x;

  auto textSize = this->progress.getSize();
  assert(textSize == this->duration.getSize());

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
  y = 8 - 2*padv;
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
