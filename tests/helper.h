#pragma once
#include <vector>
#include <functional>
#include "node.h"

using NodeRefList = std::vector<std::reference_wrapper<Node>>;

void test_NodeRefList(const NodeRefList& expected, const NodeRefList& actual);
void test_NodeRefListParent(const NodeRefList& expected, const NodeRefList& actual, const Node* parent);
bool findChild(const NodeRefList& list, const Node& child);
