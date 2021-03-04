#include "gtest/gtest.h"
#include "bitmap.h"

uint8_t data[] = { 1, 2, 3, 4, 5 };
Vec2<size_t> size{ 1,5 };

TEST(Bitmap, Constructor) {
  Bitmap a;
  Bitmap b(data, size.x, size.y);
  Bitmap d(data, size);

  EXPECT_EQ(nullptr, a.getBitmap());
  EXPECT_EQ(Vec2<size_t>(0,0), a.getSize());

  EXPECT_EQ(data, b.getBitmap());
  EXPECT_EQ(size, b.getSize());

  EXPECT_EQ(data, d.getBitmap());
  EXPECT_EQ(size, d.getSize());
}
