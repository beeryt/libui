#include "slider.h"
#include <stdio.h>

#define WIDTH 5

Slider::Slider(Node* parent) : Canvas(parent), value(0), min(0), max(100), percent(0) {}

void Slider::draw() {
  auto pos = getGlobalPosition();
  auto size = getSize();

  int width = percent * size.x;

  Rect<int16_t> filled{ pos.x, pos.y, width, size.y };
  pos.x += width;
  size.x -= width;
  Rect<int16_t> empty{ pos.x, pos.y, size.x, size.y };

  // TODO consider optional slider with border
  drawRect(filled, fg, fg);
  drawRect(empty,  fg*0.125, bg);
}

void Slider::setPercent() {
  int total = max - min;
  float percent = (float)(value - min) / total;
  if (this->percent != percent) update();
  this->percent = percent;
}

void Slider::setVal(int value) {
  if (value < min) value = min;
  if (value > max) value = max;
  if (this->value == 0 && value > 0) update();
  this->value = value;
  setPercent();
}

void Slider::setMin(int min) {
  if (min > max) setMax(min);
  if (value < min) setVal(min);
  this->min = min;
  setPercent();
}

void Slider::setMax(int max) {
  if (max < min) setMin(max);
  if (value > max) setVal(max);
  this->max = max;
  setPercent();
}

int Slider::getVal() const { return value; }
int Slider::getMin() const { return min; }
int Slider::getMax() const { return max; }
