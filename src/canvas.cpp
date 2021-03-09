#include "canvas.h"
#include <cstring>

Canvas::Canvas(Node* parent) : Node(parent) {}
void Canvas::show() { visible = true; }
void Canvas::hide() { visible = false; }
bool Canvas::isVisible() const { return visible; }

void Canvas::setSize(Vec2<> size) {
  if (this->size != size) update();
  this->size = size;
}

Vec2<> Canvas::getSize() const { return size; }

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

void Canvas::_process(uint32_t) {
  if (needUpdate) { draw(); needUpdate = false; }
}

void Canvas::process(uint32_t ms) {
  if (!visible) return;
  Node::process(ms);
}

bool Canvas::input(Event e) {
  if (!visible) return false;
  return Node::input(e);
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

void Canvas::drawLine(Vec2<> start, Vec2<> end, Color fg) {
  auto gfx = getGFXTree();
  if (!gfx) return;
  if (start == end) return;
  gfx->drawLine(start.x, start.y, end.x, end.y, fg.color);
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
  for (size_t h = 0; h < size.y; ++h) {
    for (size_t w = 0; w < size.x; ++w) {
      float scale = bitmap.getBitmap()[i++] / 255.0f;
      Color scaled = bitmap.getColor() * scale;
      gfx->drawPixel(w+pos.x,h+pos.y,scaled.color);
    }
  }
}
