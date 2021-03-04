#include "gtest/gtest.h"
#include "helper.h"
#include "text.h"

TEST(Text, Constructor) {
  const char* expected_str = "Hello World\n";
  Text a;
  Text b(&a);
  Text c(expected_str);
  Text d(&c, expected_str);

  EXPECT_EQ(nullptr, a.getParent());
  EXPECT_STREQ("", a.getText());

  EXPECT_EQ(&a, b.getParent());
  EXPECT_STREQ("", b.getText());

  EXPECT_EQ(nullptr, c.getParent());
  EXPECT_STREQ(expected_str, c.getText());

  EXPECT_EQ(&c, d.getParent());
  EXPECT_STREQ(expected_str, d.getText());
}

TEST(Text, MethodSetText) {
  const char* string1 = "Hello World\n";
  const char* string2 = "Goodbye Moon\n";

  Text a;
  a.setText(string1);
  EXPECT_STREQ(string1, a.getText());
  a.setText(string2);
  EXPECT_STREQ(string2, a.getText());
}

