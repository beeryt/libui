#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "canvas.h"

using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::AnyNumber;
using ::testing::_;

class MockGFX : public GFX {
public:
  MockGFX() : GFX(200, 200) {}
  MOCK_METHOD(void, drawPixel,      (int16_t x, int16_t y, uint16_t color), (override));
  MOCK_METHOD(void, drawLine,       (int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color), (override));
  MOCK_METHOD(void, drawFastVLine,  (int16_t x, int16_t y, int16_t h, uint16_t color), (override));
  MOCK_METHOD(void, drawFastHLine,  (int16_t x, int16_t y, int16_t w, uint16_t color), (override));
  MOCK_METHOD(void, drawRect,       (int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color), (override));
  MOCK_METHOD(void, fillRect,       (int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color), (override));
  MOCK_METHOD(void, fillScreen,     (uint16_t color), (override));
  MOCK_METHOD(void, invertDisplay,  (bool i), (override));
};

TEST(Canvas, drawRect) {
  MockGFX gfx;
  const Rect<int16_t> r{ 0, 0, 1, 1 };
  Color blue(0,0,255);
  Color red(255,0,0);

  Canvas a, b(&a);
  a.setGFX(&gfx);

  EXPECT_CALL(gfx, fillRect(_, _, _, _, blue.color)).Times(AtMost(2));
  EXPECT_CALL(gfx, drawRect(_, _, _, _, red.color)).Times(AtMost(2));
  EXPECT_CALL(gfx, fillRect(_, _, _, _, 0)).Times(AtMost(2));
  EXPECT_CALL(gfx, drawRect(_, _, _, _, 0)).Times(AtMost(2));

  a.drawRect(r, red, blue);
  a.drawRect(r, {}, {});
  b.drawRect(r, red, blue);
  b.drawRect(r, {}, {});
}

TEST(Canvas, drawText) {
  const std::string expected = "Hello World";

  MockGFX gfx;
  EXPECT_CALL(gfx, drawPixel(_, _, _)).Times(AtLeast(1));
  // TODO this is a very underwhelming test.
  // I would prefer to test that Canvas::drawChar gets called multiple times.
  // which by extension means GFX::drawChar is called, but GFX::drawChar is non-virtual
  // googletest documentation suggests changing *my* api to use templates which I don't
  // want to do at the moment (something like `Canvas<MockGFX> c;`).

  Canvas a;
  a.setGFX(&gfx);
  a.drawText({}, expected.c_str(), {}, {}, 1);
}

TEST(Bitmap, setColor) {
  Color expected{ 0xff, 0x00, 0xff };
  Bitmap b;
  b.setColor(expected);
  EXPECT_EQ(expected, b.getColor());
}

TEST(Bitmap, setBackground) {
  Color expected{ 0xff, 0x00, 0xff };
  Bitmap b;
  b.setBackground(expected);
  EXPECT_EQ(expected, b.getBackground());
}

TEST(Canvas, drawBitmap) {
  const uint8_t data[] = { 0xff,0,0xff,0 };
  Bitmap b(data, Vec2<size_t>{2,2});

  Color fg = Colors::white;
  Color bg = Colors::black;

  b.setColor(fg);
  b.setBackground(bg);

  MockGFX gfx;
  EXPECT_CALL(gfx, drawPixel(0, 0, fg.color)).Times(1);
  EXPECT_CALL(gfx, drawPixel(1, 0, bg.color)).Times(1);
  EXPECT_CALL(gfx, drawPixel(0, 1, fg.color)).Times(1);
  EXPECT_CALL(gfx, drawPixel(1, 1, bg.color)).Times(1);

  Canvas a;
  a.setGFX(&gfx);
  a.drawBitmap({}, b);
}
