#include "progressbar.h"
#include <stdio.h>

#define WIDTH 5

ProgressBar::ProgressBar(Node* parent) : Canvas(parent), value(0), min(0), max(100), percent(0) {}

void ProgressBar::draw() {
  auto pos = getGlobalPosition();
  auto size = getSize();

  int16_t width = percent * size.x;

  Rect<int16_t> filled{ pos.x, pos.y, width, size.y };
  pos.x += width;
  size.x -= width;
  Rect<int16_t> empty{ pos.x, pos.y, size.x, size.y };

  // when width is smaller than last frame, clear the empty zone
  // otherwise the center will be 'filled' from the last frame
  if (last_width != width) {
    if (width < last_width) fillRect(empty, bg);
    last_width = width;
  }

  // TODO consider making border optional
  fillRect(filled, fg);
  drawRect(empty,  fg*0.125);
}

void ProgressBar::setPercent() {
  int total = max - min;
  float percent = (float)(value - min) / total;
  if (this->percent != percent) update();
  this->percent = percent;
}

void ProgressBar::setVal(int value) {
  if (value < min) value = min;
  if (value > max) value = max;
  if (this->value == 0 && value > 0) update();
  this->value = value;
  setPercent();
}

void ProgressBar::setMin(int min) {
  if (min > max) setMax(min);
  if (value < min) setVal(min);
  this->min = min;
  setPercent();
}

void ProgressBar::setMax(int max) {
  if (max < min) setMin(max);
  if (value > max) setVal(max);
  this->max = max;
  setPercent();
}

int ProgressBar::getVal() const { return value; }
int ProgressBar::getMin() const { return min; }
int ProgressBar::getMax() const { return max; }
