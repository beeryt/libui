#include "marquee.h"
#include <cassert>
#include <cmath>

Marquee::Marquee(Node* parent, const char* text) : Text(parent, text) {}
Marquee::Marquee(const char* text) : Marquee(nullptr, text) {}

void Marquee::setSmooth(bool s) { if (smooth != s) update(); smooth = s; }
bool Marquee::getSmooth() const { return smooth; }

void Marquee::setSpeed(uint32_t s) { if (speed != s) update(); speed = s; }
uint32_t Marquee::getSpeed() const { return speed; }

void Marquee::setDebug(bool debug) { if (this->debug != debug) update(); this->debug = debug; }

void Marquee::draw() {
  int16_t charWidth = 6 * size;
  int16_t charHeight = 8 * size;
  int16_t scrnWidth = std::ceil(static_cast<float>(getSize().x) / charWidth);
  int16_t textWidth = strlen(text) * charWidth;

  if (smooth) scrnWidth++; // with smooth scrolling an additional char is needed

  // update offset
  offset += delta / speed; // advance one pixel every SPEED milliseconds
  delta %= speed; // reset delta for next draw call

  offset %= textWidth; // TODO: remove abrupt reset

  // if delay is active, reset offset
  delay_countdown -= delta;
  if (delay_countdown > 0) offset = 0;

  // prepare text for display
  int16_t charOffset = offset / charWidth;
  std::string display = std::string{ text }.substr(charOffset, scrnWidth);
  display += ' '; // empty char helps clear end-of-string as moves to left

  // determine text location
  int16_t pixelOffset = smooth ? (offset % charWidth) : 0;
  if (pixelOffset % size != 0) return; // skip, unless pixelOffset is multiple of size
  auto pos = getGlobalPosition() - Vec2<>{ pixelOffset, 0 };

  // skip draw if nothing has changed
  if (pos == last_pos && display == last_display) return;
  else { last_pos = pos; last_display = display; }

  // TODO: This draw routine could benefit from being able to draw partial chars.
  // Two methods that come to mind:
  //            1. Additional GFX::drawChar method
  //            2. Virtual GFX target which clips bounds
  // Without this feature the screen will display flickering to the left and
  // right of the marquee text.

  // draw first char
  assert(pos.x > 0);
  drawChar(pos, display[0], fg, bg, size);
  fillRect(pos, { pixelOffset, charHeight }, debug_color);

  // draw remaining text
  pos.x += charWidth;
  drawText(pos, display.substr(1).c_str(), fg, bg, size);

  if (smooth) {
    // clear last char overhang
    pos.x = getGlobalPosition().x + getSize().x;
    fillRect(pos, { charWidth, charHeight }, debug_color);
  }
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
