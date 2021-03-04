#include "gtest/gtest.h"
#include "duration.h"

TEST(Duration, Constructor) {
  Duration a;
  Duration b(7);
  Duration c(nullptr, 8);
  Duration d(&c, 9);

  EXPECT_EQ(nullptr, a.getParent());
  EXPECT_EQ(0, a.getTime());
  EXPECT_STREQ("00:00", a.getText());

  EXPECT_EQ(nullptr, b.getParent());
  EXPECT_EQ(7, b.getTime());
  EXPECT_STREQ("00:07", b.getText());

  EXPECT_EQ(nullptr, c.getParent());
  EXPECT_EQ(8, c.getTime());
  EXPECT_STREQ("00:08", c.getText());

  EXPECT_EQ(&c, d.getParent());
  EXPECT_EQ(9, d.getTime());
  EXPECT_STREQ("00:09", d.getText());
}

TEST(Duration, MethodSetTime) {
  Duration a;
  a.setTime(5);
  EXPECT_EQ(5, a.getTime());
  EXPECT_STREQ("00:05", a.getText());

  a.setTime(0);
  EXPECT_EQ(0, a.getTime());
  EXPECT_STREQ("00:00", a.getText());

  a.setTime(61);
  EXPECT_EQ(61, a.getTime());
  EXPECT_STREQ("01:01", a.getText());

  a.setTime(666);
  EXPECT_EQ(666, a.getTime());
  EXPECT_STREQ("11:06", a.getText());

  a.setTime(3600);
  EXPECT_EQ(3600, a.getTime());
  EXPECT_STREQ("1:00:00", a.getText());

  a.setTime(35999);
  EXPECT_EQ(35999, a.getTime());
  EXPECT_STREQ("9:59:59", a.getText());

  // truncates to 9:59:59
  a.setTime(36000);
  EXPECT_EQ(36000, a.getTime());
  EXPECT_STREQ("9:59:59", a.getText());

  // truncates to 9:59:59
  a.setTime(50000);
  EXPECT_EQ(50000, a.getTime());
  EXPECT_STREQ("9:59:59", a.getText());
}

