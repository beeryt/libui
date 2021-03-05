#include "text.h"
#include <string.h>
#include <algorithm>

Text::Text(Node* parent, const char* text) : Canvas(parent), text(text) { update(); }
Text::Text(Node* parent) : Text(parent, "") {}
Text::Text(const char* text) : Text(NULL, text) {}

void Text::setText(const char* text) {
  if (strcmp(this->text, text)) update();
  this->text = text;

  int lines = 1;
  int width = 0;

  // for each char: increment count
  // on newline: set width & increment lines & reset count
  int count = 0;
  for (int i = 0; i < strlen(text); ++i) {
    if (text[i] == '\n') {
      lines++;
      width = std::max(width, count);
      count = 0;
    } else { count++; }
  }
  width = std::max(width, count);

  // set size based on new text
  setSize({
    static_cast<int16_t>(6 * width),
    static_cast<int16_t>(8 * lines)
  });
}
const char* Text::getText() const { return text; }

void Text::draw() {
  drawText(getGlobalPosition(), text, fg, bg, size);
}

