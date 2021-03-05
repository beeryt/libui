#include "button.h"

Button::Button(Node* parent) : BaseButton(parent) {
  addChild(text);
  text.setBackground(bg);
}

bool Button::hasPoint(Vec2<> p) const {
  return Canvas::hasPoint(p) || text.hasPoint(p);
}

void Button::setBackground(Color color) {
  if (bg != color) update();
  bg = color;
  text.setBackground(color);
}

void Button::draw() {
  Vec2<> size{ std::max(getSize().x, text.getSize().x), std::max(getSize().y, text.getSize().y) };
  drawRect(getGlobalPosition(), size, bg, bg);
}
