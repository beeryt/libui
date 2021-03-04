#include "gtest/gtest.h"
#include "sprite.h"

TEST(Sprite, Constructor) {
  Sprite a, b(&a);

  EXPECT_EQ(1, a.getChildren().size());
  EXPECT_EQ(0, b.getChildren().size());
  EXPECT_EQ(Bitmap{}, a.getTexture());
  EXPECT_EQ(Bitmap{}, b.getTexture());
}

TEST(Sprite, setTexture) {
  uint8_t data[] = { 0xFF, 0x00, 0xFF, 0x00 };
  Bitmap b1(data, { 2,2 });

  Sprite a;
  a.setTexture(b1);
  EXPECT_EQ(b1, a.getTexture());
}
