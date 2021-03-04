#include "gtest/gtest.h"
#include "playback.h"

TEST(Playback, Constructor) {
  Playback a;
  Playback b(&a);
  Playback c(&b, 4);
  Playback d(7);

  EXPECT_EQ(nullptr, a.getParent());
  EXPECT_EQ(0, a.getProgress());
  EXPECT_EQ(0, a.getDuration());

  EXPECT_EQ(&a, b.getParent());
  EXPECT_EQ(0, b.getProgress());
  EXPECT_EQ(0, b.getDuration());

  EXPECT_EQ(&b, c.getParent());
  EXPECT_EQ(0, c.getProgress());
  EXPECT_EQ(4, c.getDuration());

  EXPECT_EQ(nullptr, d.getParent());
  EXPECT_EQ(0, d.getProgress());
  EXPECT_EQ(7, d.getDuration());
}

TEST(Playback, MethodSetProgress) {
  Playback a(60);

  a.setProgress(40);
  EXPECT_EQ(40, a.getProgress());
  EXPECT_EQ(60, a.getDuration());

  a.setProgress(60);
  EXPECT_EQ(60, a.getProgress());
  EXPECT_EQ(60, a.getDuration());

  a.setProgress(0);
  EXPECT_EQ(0, a.getProgress());
  EXPECT_EQ(60, a.getDuration());
}

TEST(Playback, MethodSetProgressGreaterThanDuration) {
  Playback a(30);

  a.setProgress(60);
  EXPECT_EQ(60, a.getProgress());
  EXPECT_EQ(30, a.getDuration());
}

TEST(Playback, MethodSetDuration) {
  Playback a;

  a.setDuration(50);
  EXPECT_EQ(50, a.getDuration());
  EXPECT_EQ(0, a.getProgress());

  a.setDuration(0);
  EXPECT_EQ(0, a.getDuration());
  EXPECT_EQ(0, a.getProgress());
}

TEST(Playback, MethodSetDurationLessThanProgress) {
  Playback a(60);
  a.setProgress(30);
  a.setDuration(10);

  EXPECT_EQ(30, a.getProgress());
  EXPECT_EQ(10, a.getDuration());
}

