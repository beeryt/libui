#include "bitmap.h"
#include <cstring>

Bitmap::Bitmap() : Bitmap(nullptr, 0, 0) {}
Bitmap::Bitmap(const uint8_t *bitmap, size_t w, size_t h) : Bitmap(bitmap, {w,h}) {}
Bitmap::Bitmap(const uint8_t *bitmap, Vec2<size_t> size) : bitmap(bitmap), size(size) {}
bool Bitmap::operator==(const Bitmap& rhs) const {
  if (size != rhs.size) { return false; }
  // we can shortcut if the two objects share the same pointers
  if (bitmap == rhs.bitmap) return true;
  // otherwise we will have to compare memory contents
  // note: however, this is too expensive instead just assume different
  return false;
#if 0
  if (memcmp(bitmap, rhs.bitmap, size.dot())) return false;
  return true;
#endif
}

bool Bitmap::operator!=(const Bitmap& rhs) const {
  return !(*this == rhs);
}

bool Bitmap::isComplete() const {
  return size.x && size.y && bitmap;
}

void Bitmap::setBitmap(const uint8_t *b, size_t x, size_t y) { setBitmap(b, { x,y }); }
void Bitmap::setBitmap(const uint8_t *b, Vec2<size_t> s) {
  this->bitmap = b;
  this->size = s;
}

const uint8_t* Bitmap::getBitmap() const { return bitmap; }

Vec2<size_t> Bitmap::getSize() const { return size; }
bool operator==(const Color& a, const Color& b) { return a.color == b.color; }