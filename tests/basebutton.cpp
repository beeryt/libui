#include "gtest/gtest.h"
#include "helper.h"
#include "basebutton.h"

class CountingButton : public BaseButton {
  public:
    void draw() override { drawCount++; }
    void modeChanged() override { modeCount++; };
    int drawCount = 0;
    int modeCount = 0;
};

TEST(BaseButton, Constructor) {
  BaseButton a, b(&a);

  EXPECT_EQ(1, a.getChildren().size());
  EXPECT_EQ(0, b.getChildren().size());
  findChild(a.getChildren(), b);
  EXPECT_EQ(ButtonMode::NORMAL, a.getMode());
  EXPECT_TRUE(a.isEnabled());
}

TEST(BaseButton, DISABLED_setOnClick) {
  BaseButton a;

  int count = 0;
  // TODO: figure out how this can work
  //a.setOnClick([&count](){ count++; });
  a.input({ Event::RELEASE, {0,0} });
  a.input({ Event::RELEASE, {1,1} });

  EXPECT_EQ(1, count);
}

TEST(BaseButton, disable) {
  BaseButton a;
  a.enable();
  a.disable();
  EXPECT_FALSE(a.isEnabled());
  EXPECT_FALSE(a.isInputEnabled());
  EXPECT_EQ(ButtonMode::DISABLED, a.getMode());
}

TEST(BaseButton, enable) {
  BaseButton a;
  a.disable();
  a.enable();
  EXPECT_TRUE(a.isEnabled());
  EXPECT_TRUE(a.isInputEnabled());
  EXPECT_NE(ButtonMode::DISABLED, a.getMode());
}

TEST(BaseButton, getMode) {
  BaseButton a;
  Vec2<> pos{ 0,0 };

  EXPECT_EQ(ButtonMode::NORMAL, a.getMode());
  a.input({ Event::TOUCH, pos });
  EXPECT_EQ(ButtonMode::PRESSED, a.getMode());
  a.disable();
  EXPECT_EQ(ButtonMode::DISABLED, a.getMode());
  a.enable();
  EXPECT_EQ(ButtonMode::PRESSED, a.getMode());
  a.input({ Event::RELEASE, pos });
  EXPECT_EQ(ButtonMode::NORMAL, a.getMode());
}

TEST(BaseButton, input) {
  CountingButton a;

  auto expect_state = [&a](ButtonMode mode) {
    EXPECT_EQ(mode, a.getMode());
  };
#define EXPECT_STATE(...) { SCOPED_TRACE("EXPECT_STATE"); expect_state(__VA_ARGS__); }

  EXPECT_STATE(ButtonMode::NORMAL);

  a.process();
  EXPECT_STATE(ButtonMode::NORMAL);

  a.input({ Event::TOUCH, {1,1} }); // missed input
  EXPECT_STATE(ButtonMode::NORMAL);

  a.input({ Event::TOUCH, {0,0} }); // handled input
  EXPECT_STATE(ButtonMode::PRESSED);

  a.process();
  EXPECT_STATE(ButtonMode::PRESSED);

  a.input({ Event::RELEASE, {0,0} }); // handled input
  EXPECT_STATE(ButtonMode::NORMAL);

  a.process();
  EXPECT_STATE(ButtonMode::NORMAL);

  a.process();
  a.disable();
  EXPECT_STATE(ButtonMode::DISABLED);

  a.process();
  a.input({ Event::TOUCH, {0,0} }); // disabled input
  EXPECT_STATE(ButtonMode::DISABLED);

  a.process();
  a.input({ Event::RELEASE, {0,0} }); // disabled input
  EXPECT_STATE(ButtonMode::DISABLED);

  a.process();
  a.enable();
  EXPECT_STATE(ButtonMode::NORMAL);

  EXPECT_EQ(1, a.drawCount);
  EXPECT_EQ(4, a.modeCount);
}
