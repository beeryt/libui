#pragma once
#include <stdint.h>

constexpr uint16_t map(uint16_t x, uint16_t imin, uint16_t imax, uint16_t omin, uint16_t omax) {
  return (x - imin) * (omax - omin) / (imax - imin) + omin;
}

constexpr uint16_t rgb_to_c(uint8_t r, uint8_t g, uint8_t b) {
  return
    map(b, 0, 0xFF, 0, 0x1F) << 0 |
    map(g, 0, 0xFF, 0, 0x3F) << 5 |
    map(r, 0, 0xFF, 0, 0x1F) << 11;
}

constexpr void c_to_rgb(uint16_t c, uint8_t *r, uint8_t *g, uint8_t *b) {
  if (r) *r = (c >> 0xB) & 0x1F;
  if (g) *g = (c >> 0x5) & 0x3F;
  if (b) *b = (c >> 0x0) & 0x1F;
}

struct Color {
  uint16_t color;

  Color(uint16_t c = 0) : color(c) {}
  Color(uint8_t r, uint8_t g, uint8_t b) : Color(rgb_to_c(r, g, b)) {}

  bool operator==(const Color& b) { return color == b.color; }
  bool operator!=(const Color& b) { return color != b.color; }

  Color operator*(float scale) const {
    Color a = *this;
    uint8_t r,g,b;
    c_to_rgb(a.color, &r,&g,&b);
    r = static_cast<uint8_t>(scale * map(r, 0, 0x1F, 0, 0xFF));
    g = static_cast<uint8_t>(scale * map(g, 0, 0x3F, 0, 0xFF));
    b = static_cast<uint8_t>(scale * map(b, 0, 0x1F, 0, 0xFF));
    a.color = rgb_to_c(r,g,b);
    return a;
  }

};

bool operator==(const Color& a, const Color& b);

namespace Colors {
  const static Color white = Color{ 0xFF, 0xFF, 0xFF };
  const static Color black = Color{ 0x00, 0x00, 0x00 };
  const static Color magenta = Color{ 0xFF, 0x00, 0xFF };
}

