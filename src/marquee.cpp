#include "marquee.h"
#include <cassert>
#include <string>
#include <cmath>

Marquee::Marquee(Node* parent, const char* text) : Text(parent, text) {}
Marquee::Marquee(const char* text) : Marquee(nullptr, text) {}

void Marquee::setSmooth(bool s) { if (smooth != s) update(); smooth = s; }
bool Marquee::getSmooth() const { return smooth; }

void Marquee::setSpeed(uint32_t s) { if (speed != s) update(); speed = s; }
uint32_t Marquee::getSpeed() const { return speed; }

void Marquee::setDebug(bool debug) { if (this->debug != debug) update(); this->debug = debug; }

void Marquee::draw() {
  const int16_t charWidth = 6 * size;

  // update the pixel offset
  int pixelShift = delta / speed; // one pixel every speed milliseconds
  offset += pixelShift;
  int maxWidth = strlen(text) * charWidth;
  offset %= maxWidth;

  // if delay is active reset offset
  delay_countdown -= delta;
  if (delay_countdown > 0) { offset = 0; }

  // figure out how many chars are truncated from start of string
  unsigned truncatedChars = offset / charWidth;
  assert(truncatedChars < strlen(text));

  // prepare the substr for
  size_t maxChars = std::ceil(static_cast<float>(getSize().x) / charWidth);
  size_t extraPixels = (maxChars * charWidth) % getSize().x;
  if (smooth) maxChars++; // smooth scrolling allows a single extra char
  std::string str = std::string{ text }.substr(truncatedChars, maxChars);

  const auto color = debug ? debug_color : bg;

  // clear drawing zone
  drawRect(getGlobalPosition(), getSize(), bg, bg);

  // iff smooth: find sub-char pixel offset
  int16_t charOffset = smooth ? offset % charWidth : 0;

  // draw text
  auto pos = getGlobalPosition();
  pos.x -= charOffset;
  drawText(pos, str.c_str(), fg, bg, size);

  // clear left-overhang
  Vec2<> s{ charWidth, getSize().y };
  pos.x = getGlobalPosition().x - charWidth;
  drawRect(pos, s, color, color);

  // clear right-overhang
  pos.x = getGlobalPosition().x + getSize().x;
  s.x = extraPixels + (smooth ? s.x : 0);
  drawRect(pos, s, color, color);

  // reset delta for next draw call
  delta %= speed;
}

void Marquee::process(uint32_t ms) {
  const bool needToSlide = strlen(text) > static_cast<size_t>(getSize().x / (6 * size));
  if (needToSlide) {
    if (ms > 0) update();
    delta += ms;
  }
  else {
    delta = 0;
  }
  Text::process(ms);
}
