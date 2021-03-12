#include "gtest/gtest.h"
#include "node.h"
#include "helper.h"

#include <cstring>
#include <cstdint>

using NodeList = std::vector<std::reference_wrapper<Node>>;

TEST(Node, Constructor) {
	Node a;
	Node b, c(&b);

	// default constructor has no parent and no children
	EXPECT_EQ(nullptr, a.getParent());
	EXPECT_EQ(0, a.getChildren().size());

	// constructor does not modify parent's parent
	EXPECT_EQ(nullptr, b.getParent());
	// construcor adds constructed to parent's children
	EXPECT_EQ(1, b.getChildren().size());
	EXPECT_EQ(&c, &b.getChildren()[0].get());
	// constructor sets parent
	EXPECT_EQ(&b, c.getParent());
}

TEST(Node, Destructor) {
	Node* a = new Node;
	Node b(a), c(a), d(&c);

	NodeList expectedChildren = { b, c };

	EXPECT_EQ(nullptr, a->getParent());
	EXPECT_EQ(a, b.getParent());
	EXPECT_EQ(a, c.getParent());
	EXPECT_EQ(&c, d.getParent());

	delete a;

	EXPECT_EQ(nullptr, b.getParent());
	EXPECT_EQ(nullptr, c.getParent());
	EXPECT_EQ(&c, d.getParent());
}

TEST(Node, addChild) {
	Node a, b, c, d, e, f;
	NodeList nodes = { a,b,c,d,e,f };
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		EXPECT_EQ(nullptr, it->get().getParent());
		EXPECT_EQ(0, it->get().getChildren().size());
	}

	a.addChild(b);
	a.addChild(c);
	a.addChild(d);
	b.addChild(e);
	e.addChild(f);

	EXPECT_EQ(nullptr, a.getParent());
	test_NodeRefListParent({ b,c,d }, a.getChildren(), &a);
	EXPECT_EQ(&a, b.getParent());
	test_NodeRefListParent({ e }, b.getChildren(), &b);
	EXPECT_EQ(&a, c.getParent());
	test_NodeRefList({}, c.getChildren());
	EXPECT_EQ(&a, d.getParent());
	test_NodeRefList({}, d.getChildren());
	EXPECT_EQ(&b, e.getParent());
	test_NodeRefListParent({ f }, e.getChildren(), &e);
	EXPECT_EQ(&e, f.getParent());
	test_NodeRefList({}, f.getChildren());
}

TEST(Node, removeChild) {
	Node a, b(&a), c(&a), d(&a), e(&d);

	test_NodeRefListParent({ b,c,d }, a.getChildren(), &a);
	test_NodeRefListParent({ e }, d.getChildren(), &d);

	a.removeChild(d);

	EXPECT_EQ(nullptr, d.getParent());
	test_NodeRefListParent({ b,c }, a.getChildren(), &a);
	test_NodeRefListParent({ e }, d.getChildren(), &d);
}

TEST(Node, removeChildInvalid) {
  Node a, b(&a), c, d(&c);
  a.removeChild(d);

  EXPECT_EQ(nullptr, a.getParent());
  EXPECT_EQ(&a, b.getParent());
  test_NodeRefListParent({ b }, a.getChildren(), &a);

  EXPECT_EQ(nullptr, c.getParent());
  EXPECT_EQ(&c, d.getParent());
  test_NodeRefListParent({ d }, c.getChildren(), &c);
}

