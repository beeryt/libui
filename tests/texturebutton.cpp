#include "gtest/gtest.h"
#include "helper.h"
#include "texturebutton.h"

TEST(TextureButton, Constructor) {
  TextureButton a, b, c(&b);

  EXPECT_EQ(1, a.getChildren().size());
  EXPECT_EQ(2, b.getChildren().size());
  EXPECT_EQ(1, c.getChildren().size());
  findChild(b.getChildren(), c);
}
