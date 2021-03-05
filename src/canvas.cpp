#include "canvas.h"
#include <cstring>

Canvas::Canvas(Node* parent) : Node(parent) {}
void Canvas::show() { visible = true; }
void Canvas::hide() { visible = false; }
bool Canvas::isVisible() const { return visible; }

void Canvas::update() { needDraw = true; }

bool Canvas::willDraw() const { return needDraw; }

void Canvas::setSize(Vec2<> size) {
  if (this->size != size) update();
  this->size = size;
}

Vec2<> Canvas::getSize() const { return size; }

void Canvas::setPosition(Vec2<> pos) {
  if (this->position != pos) { update(); }
  this->position = pos;
}

Vec2<> Canvas::getPosition() const { return position; }

Vec2<> Canvas::getGlobalPosition() const {
  Vec2<> accumulator;
  const Node* n = this;
  while (n) {
      // attempt to cast to Canvas*
      // with -fno-exceptions set I am making an assumption that
      // dynamic_cast returns nullptr on std::bad_cast
      auto c = dynamic_cast<const Canvas*>(n);
      if (c) accumulator += c->position;
    n = n->getParent();
  }
  return accumulator;
}

Rect<> Canvas::getRect() const {
  return {
    getGlobalPosition().x,
    getGlobalPosition().y,
    getSize().x,
    getSize().y
  };
}

bool Canvas::hasPoint(Vec2<> point) const {
  Rect<> bounds = getRect();
  return point.x >= bounds.x && point.x <= bounds.x + bounds.w
    && point.y >= bounds.y && point.y <= bounds.y + bounds.h;
}

void Canvas::draw() {}

void Canvas::_process() {
  if (needDraw) { draw(); needDraw = false; }
}

void Canvas::process() {
  if (!visible) return;
  Node::process();
}

bool Canvas::input(Event e) {
  if (!visible) return false;
  return Node::input(e);
}

void Canvas::setGFX(GFX* gfx) { this->gfx = gfx; update(); }
GFX* Canvas::getGFX() const { return gfx; }
GFX* Canvas::getGFXTree() const {
  GFX* gfx = nullptr;
  const Node* n = this;
  while (!gfx && n) {
    auto c = dynamic_cast<const Canvas*>(n);
    if (c) gfx = c->getGFX();
    n = n->getParent();
  }
  return gfx;
}

void Canvas::drawRect(Vec2<int16_t> pos, Vec2<int16_t> size, Color border, Color fill) {
  auto gfx = getGFXTree();
  if (!gfx) return;
  if (size.x == 0 || size.y == 0) return;
  gfx->fillRect(pos.x,pos.y,size.x,size.y,fill.color);
  gfx->drawRect(pos.x, pos.y, size.x, size.y, border.color);
}

void Canvas::drawRect(Rect<int16_t> rect, Color border, Color fill) {
  drawRect({ rect.x,rect.y }, { rect.w,rect.h }, border, fill);
}

void Canvas::drawChar(Vec2<int16_t> position, char c, Color color, Color bg, uint8_t size) {
  auto gfx = getGFXTree();
  if (!gfx) return;
  gfx->drawChar(position.x, position.y, c, color.color, bg.color, size);
}

void Canvas::drawText(Vec2<int16_t> position, const char* text, Color color, Color bg, uint8_t size) {
  auto gfx = getGFXTree();
  if (!gfx) return;
  auto cursor = position;
  for (size_t i = 0; i < strlen(text); ++i) {
    // detect newlines and move cursor
    if (text[i] == '\n') {
      cursor.x = position.x;
      cursor.y += size*8;
      continue;
    }
    // otherwise draw char and move cursor
    gfx->drawChar(cursor.x, cursor.y, text[i], color.color, bg.color, size);
    cursor.x += size*6;
  }
}

// note: Latest Adafruit_GFX has a GFX::drawRGBBitmap method.
// Unfortunately that is not in this version, so everything is monochrome.
void Canvas::drawBitmap(Vec2<int16_t> pos, Bitmap bitmap) {
  auto gfx = getGFXTree();
  if (!gfx) return;
  auto size = bitmap.getSize();
  int i = 0;
  for (int16_t h = 0; h < size.y; ++h) {
    for (int16_t w = 0; w < size.x; ++w) {
      float scale = bitmap.getBitmap()[i++] / 255.0f;
      Color scaled = bitmap.getColor() * scale;
      gfx->drawPixel(w+pos.x,h+pos.y,scaled.color);
    }
  }
}
