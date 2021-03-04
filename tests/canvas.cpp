#include "gtest/gtest.h"
#include "canvas.h"

class CountingCanvas : public Canvas {
  public:
    using Canvas::Canvas;
    void draw() override { drawCount++; };
    bool _input(Event) override { inputCount++; return handled; }
    void setHandled(bool h) { handled = h; }
    bool handled = true;
    int drawCount = 0;
    int inputCount = 0;
};

TEST(Canvas, Constructor) {
  Canvas a;
  Canvas b(&a);

  EXPECT_EQ(nullptr, a.getParent());
  EXPECT_EQ(1, a.getChildren().size());
  EXPECT_EQ(Vec2<>{}, a.getSize());
  EXPECT_EQ(Vec2<>{}, a.getPosition());
  EXPECT_EQ(Vec2<>{}, a.getGlobalPosition());
  EXPECT_EQ(Rect<>{}, a.getRect());
  EXPECT_TRUE(a.willDraw());
  EXPECT_EQ(nullptr, a.getGFX());
  EXPECT_EQ(nullptr, a.getGFXTree());

  EXPECT_EQ(&a, b.getParent());
  EXPECT_EQ(0, b.getChildren().size());
  EXPECT_EQ(Vec2<>{}, b.getSize());
  EXPECT_EQ(Vec2<>{}, b.getPosition());
  EXPECT_EQ(Vec2<>{}, b.getGlobalPosition());
  EXPECT_EQ(Rect<>{}, b.getRect());
  EXPECT_TRUE(b.willDraw());
  EXPECT_EQ(nullptr, b.getGFX());
  EXPECT_EQ(nullptr, b.getGFXTree());
}

TEST(Canvas, show) {
  Canvas a;
  a.show();
  EXPECT_TRUE(a.isVisible());
}

TEST(Canvas, hide) {
  Canvas a;
  a.hide();
  EXPECT_FALSE(a.isVisible());
}

TEST(Canvas, MethodSetSize) {
  Canvas a;
  auto expected = Vec2<>{ 1, 2 };

  a.process();
  a.setSize(expected);
  EXPECT_EQ(expected, a.getSize());
  EXPECT_TRUE(a.willDraw());

  a.process();
  a.setSize(Vec2<>{});
  EXPECT_EQ(Vec2<>{}, a.getSize());
  EXPECT_TRUE(a.willDraw());

  a.process();
  a.setSize(Vec2<>{});
  EXPECT_EQ(Vec2<>{}, a.getSize());
  EXPECT_FALSE(a.willDraw());
}

TEST(Canvas, MethodSetPosition) {
  Canvas a;
  auto expected = Vec2<>{ 3, 4 };

  a.process();
  a.setPosition(expected);
  EXPECT_EQ(expected, a.getPosition());
  EXPECT_TRUE(a.willDraw());

  a.process();
  a.setPosition(Vec2<>{});
  EXPECT_EQ(Vec2<>{}, a.getPosition());
  EXPECT_TRUE(a.willDraw());

  a.process();
  a.setPosition(Vec2<>{});
  EXPECT_EQ(Vec2<>{}, a.getPosition());
  EXPECT_FALSE(a.willDraw());
}

TEST(dynamic_cast, bad_cast_is_null) {
  Node n;
  auto c = dynamic_cast<Canvas*>(&n);
  EXPECT_EQ(nullptr, c);
}

TEST(Canvas, MethodGetGlobalPosition) {
  Canvas a;
  Canvas b(&a);

  Vec2<> aPos{ 0, 5 };
  Vec2<> bPos{ 0, 5 };
  Vec2<> gPos = aPos + bPos;

  a.setPosition(aPos);
  b.setPosition(bPos);

  EXPECT_EQ(aPos, a.getPosition());
  EXPECT_EQ(bPos, b.getPosition());

  EXPECT_EQ(aPos, a.getGlobalPosition());
  EXPECT_EQ(gPos, b.getGlobalPosition());
}

TEST(Canvas, MethodGetGlobalPositionMixedTypes) {
  Canvas a;
  Node b(&a);
  Canvas c(&b);

  Vec2<> aPos{ 0, 5 };
  Vec2<> cPos{ 5, 0 };
  Vec2<> gPos = aPos + cPos;

  a.setPosition(aPos);
  c.setPosition(cPos);

  EXPECT_EQ(aPos, a.getPosition());
  EXPECT_EQ(cPos, c.getPosition());

  EXPECT_EQ(aPos, a.getGlobalPosition());
  EXPECT_EQ(gPos, c.getGlobalPosition());
}

TEST(Canvas, getRect) {
  Canvas a, b(&a);
  Rect<> expected{ 1,2,3,4 };
  a.setPosition({ expected.x, expected.y });
  a.setSize({ expected.w, expected.h });
  b.setSize(a.getSize());
  EXPECT_EQ(expected, a.getRect());
  EXPECT_EQ(expected, b.getRect());
}

TEST(Canvas, hasPoint) {
  Canvas a;
  a.setPosition({ 5,5 });
  a.setSize({ 2,2 });

  for (int16_t i = 0; i < 10; ++i) {
    for (int16_t j = 0; j < 10; ++j) {
      bool outside = i < 5 || i > 7 || j < 5 || j > 7;
      EXPECT_EQ(!outside, a.hasPoint({ i,j }));
    }
  }
}

TEST(Canvas, setGFX) {
  Canvas a, b(&a);
  GFX* expected = (GFX*)0x0001;

  a.setGFX(expected);
  EXPECT_EQ(expected, a.getGFX());
  EXPECT_EQ(expected, a.getGFXTree());
  EXPECT_EQ(nullptr, b.getGFX());
  EXPECT_EQ(expected, b.getGFXTree());

  b.setGFX(expected);
  a.setGFX(nullptr);
  EXPECT_EQ(nullptr, a.getGFX());
  EXPECT_EQ(nullptr, a.getGFXTree());
  EXPECT_EQ(expected, b.getGFX());
  EXPECT_EQ(expected, b.getGFXTree());
}

TEST(Canvas, update) {
  Canvas a;
  a.process();
  EXPECT_FALSE(a.willDraw());
  a.update();
  EXPECT_TRUE(a.willDraw());
}

#define EXPECT_COUNT(...) { SCOPED_TRACE("EXPECT_COUNT"); expect_count(__VA_ARGS__); }

TEST(Canvas, input) {
  CountingCanvas a, b(&a), c(&b);

  auto setHandled = [&](bool ha, bool hb, bool hc) {
    a.setHandled(ha);
    b.setHandled(hb);
    c.setHandled(hc);
  };

  auto expect_count = [&](int ca, int cb, int cc) {
    EXPECT_EQ(ca, a.inputCount);
    EXPECT_EQ(cb, b.inputCount);
    EXPECT_EQ(cc, c.inputCount);
  };

  setHandled(false, false, false);
  a.input({});
  EXPECT_COUNT(1,1,1);

  setHandled(false, false, true);
  a.input({});
  EXPECT_COUNT(1,1,2);

  setHandled(false, true, false);
  a.input({});
  EXPECT_COUNT(1,2,3);

  setHandled(false, true, true);
  a.input({});
  EXPECT_COUNT(1,2,4);

  setHandled(true, false, false);
  a.input({});
  EXPECT_COUNT(2,3,5);

  setHandled(true, false, true);
  a.input({});
  EXPECT_COUNT(2,3,6);

  setHandled(true, true, false);
  a.input({});
  EXPECT_COUNT(2,4,7);

  setHandled(true, true, true);
  a.input({});
  EXPECT_COUNT(2,4,8);

  b.hide();
  a.input({});
  EXPECT_COUNT(3,4,8);
}

TEST(Canvas, process) {
  CountingCanvas a, b(&a), c(&a), d(&b);

  auto expect_count = [&](int ca, int cb, int cc, int cd) {
    EXPECT_EQ(ca, a.drawCount);
    EXPECT_EQ(cb, b.drawCount);
    EXPECT_EQ(cc, c.drawCount);
    EXPECT_EQ(cd, d.drawCount);
  };

  auto update = [&]() { a.update(); b.update(); c.update(); d.update(); };

  a.process();
  EXPECT_COUNT(1,1,1,1);
  update();

  b.process();
  EXPECT_COUNT(1,2,1,2);
  update();

  c.process();
  EXPECT_COUNT(1,2,2,2);
  update();

  d.process();
  EXPECT_COUNT(1,2,2,3);
  update();

  b.hide();
  a.process();
  EXPECT_COUNT(2,2,3,3);
}

