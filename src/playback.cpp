#include "playback.h"

Playback::Playback(Node* parent, int duration)
  : Canvas(parent), progress(0), duration(duration) {
  slider.setMin(0);
  slider.setVal(0);
  slider.setMax(duration);
  addChild(this->progress);
  addChild(this->slider);
  addChild(this->duration);
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
