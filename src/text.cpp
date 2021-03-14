#include "text.h"
#include <string.h>
#include <algorithm>

Text::Text(Node* parent, const char* text) : Canvas(parent), text(text) { update(); }
Text::Text(Node* parent) : Text(parent, "") {}
Text::Text(const char* text) : Text(NULL, text) {}

void Text::setBackground(Color color) { if (bg.color != color.color) update(); bg = color; }

void Text::setTextSize(uint8_t s) {
  if (size != s) update();
  size = s;
  setText(text);
}
uint8_t Text::getTextSize() const { return size; }

void Text::setText(const char* text, bool updateSize) {
  update(); // always assume update
  this->text = text;

  if (updateSize) {
    int lines = 1;
    int width = 0;

    if (text) {
      // for each char: increment count
      // on newline: set width & increment lines & reset count
      int count = 0;
      for (unsigned i = 0; i < strlen(text); ++i) {
        if (text[i] == '\n') {
          lines++;
          width = std::max(width, count);
          count = 0;
        } else { count++; }
      }
      width = std::max(width, count);
    }

    // set size based on new text
    setSize({
      static_cast<int16_t>(6 * width * size),
      static_cast<int16_t>(8 * lines * size)
    });
  }
}
const char* Text::getText() const { return text; }

void Text::draw() {
  drawText(getGlobalPosition(), text, fg, bg, size);
}

