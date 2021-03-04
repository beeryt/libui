#include "text.h"
#include <string.h>

Text::Text(Node* parent, const char* text) : Canvas(parent), text(text) { update(); }
Text::Text(Node* parent) : Text(parent, "") {}
Text::Text(const char* text) : Text(NULL, text) {}

void Text::setText(const char* text) {
  if (strcmp(this->text, text)) update();
  this->text = text;
}
const char* Text::getText() const { return text; }

void Text::draw() {
  drawText(getGlobalPosition(), text, fg, bg, size);
}

