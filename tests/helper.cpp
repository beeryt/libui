#include "helper.h"
#include "gtest/gtest.h"

void test_NodeRefList(const NodeRefList& expected, const NodeRefList& actual) {
  EXPECT_EQ(expected.size(), actual.size());
  for (size_t i = 0; i < actual.size(); ++i) {
    EXPECT_EQ(&expected[i].get(), &actual[i].get());
  }
}

bool findChild(const NodeRefList& list, const Node& child) {
  bool found = false;
  for (auto it = list.begin(); it != list.end(); ++it) {
    if (&child == &it->get()) found = true;
  }
  return found;
}

void test_NodeRefListParent(const NodeRefList& expected, const NodeRefList& actual, const Node* parent) {
  EXPECT_EQ(expected.size(), actual.size());
  for (size_t i = 0; i < actual.size(); ++i) {
    EXPECT_EQ(&expected[i].get(), &actual[i].get());
    EXPECT_EQ(parent, actual[i].get().getParent());
  }
}
