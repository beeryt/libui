#include "gtest/gtest.h"
#include "helper.h"
#include "slider.h"

TEST(Slider, Constructor) {
  Slider a;
  EXPECT_EQ(0, a.getMin());
  EXPECT_EQ(0, a.getVal());
  EXPECT_EQ(100, a.getMax());
}

TEST(Slider, setVal) {
  Slider a;

  a.setVal(50);

  EXPECT_EQ(50, a.getVal());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setValUpdates) {
  Slider a;

  a.process();
  EXPECT_FALSE(a.willDraw());

  a.setVal(4);
  EXPECT_TRUE(a.willDraw());
}

TEST(Slider, setValGreaterThanMax) {
  Slider a;
  a.setVal(200);

  // clamped to max
  EXPECT_EQ(100, a.getVal());
  // no change to max
  EXPECT_EQ(100, a.getMax());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setValLessThanMin) {
  Slider a;
  a.setVal(-200);

  // clamped to min
  EXPECT_EQ(0, a.getVal());
  // no change to min
  EXPECT_EQ(0, a.getMin());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setMin) {
  Slider a;
  a.setMin(-10);

  EXPECT_EQ(-10, a.getMin());
  // no change to other fields
  EXPECT_EQ(0, a.getVal());
  EXPECT_EQ(100, a.getMax());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setMinUpdates) {
  Slider a;

  a.process();
  EXPECT_FALSE(a.willDraw());

  a.setMin(4);
  EXPECT_TRUE(a.willDraw());
}

TEST(Slider, setMinGreaterThanValue) {
  Slider a;
  a.setMin(10);

  EXPECT_EQ(10, a.getMin());
  // change in value
  EXPECT_EQ(10, a.getVal());
  // no change to max bound
  EXPECT_EQ(100, a.getMax());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setMinGreaterThanMax) {
  Slider a;
  a.setMin(200);

  EXPECT_EQ(200, a.getMin());
  // change in value and max bound
  EXPECT_EQ(200, a.getVal());
  EXPECT_EQ(200, a.getMax());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setMax) {
  Slider a;
  a.setMax(50);

  EXPECT_EQ(50, a.getMax());
  // no change to other fields
  EXPECT_EQ(0, a.getVal());
  EXPECT_EQ(0, a.getMin());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setMaxUpdates) {
  Slider a;

  a.setVal(1); // an update is needed only if the percentage changes
  a.process();
  EXPECT_FALSE(a.willDraw());

  a.setMax(4);
  EXPECT_TRUE(a.willDraw());
}

TEST(Slider, setMaxLessThanValue) {
  Slider a;
  a.setVal(50);
  a.setMax(10);

  EXPECT_EQ(10, a.getMax());
  // change in value
  EXPECT_EQ(10, a.getVal());
  // no change to min bound
  EXPECT_EQ(0, a.getMin());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

TEST(Slider, setMaxLessThanMin) {
  Slider a;
  a.setMax(-200);

  EXPECT_EQ(-200, a.getMax());
  // change in value and min bound
  EXPECT_EQ(-200, a.getVal());
  EXPECT_EQ(-200, a.getMin());
  // value is within bounds
  EXPECT_LE(a.getMin(), a.getVal());
  EXPECT_GE(a.getMax(), a.getVal());
}

