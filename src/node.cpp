#include "node.h"

Node::Node(Node* parent) : parent(parent) {
  if (parent) {
    parent->addChild(*this);
  }
}

Node::~Node() {
  for (auto it = children.begin(); it != children.end(); ++it) {
    it->get().parent = nullptr;
  }
}

Node* Node::getParent() const { return parent; }

const Node::NodeList& Node::getChildren() const {
  return children;
}

void Node::addChild(Node& child) {
  if (child.parent) {
    child.parent->removeChild(child);
  }
  children.push_back(child);
  child.parent = this;
}

void Node::removeChild(Node& child) {
  for (auto it = children.begin(); it != children.end(); ++it) {
    if (&it->get() == &child) {
      children.erase(it);
      child.parent = nullptr;
      break;
    }
  }
}

// process in pre-order so parents can update children first
void Node::process(uint32_t ms) {
  _process(ms);
  auto it = children.begin();
  while (it != children.end()) { (*it++).get().process(ms); }
}

// input is in post-order so children can handle input before parent
bool Node::input(Event event) {
  for (auto it = children.begin(); it != children.end(); ++it) {
    auto& n = it->get();
    if (n.input(event)) return true;
  }
  return _input(event);
}

void Node::_process(uint32_t) {}
bool Node::_input(Event) {
  return false;
}
void Node::setPosition(Vec2<> pos) {
  if (this->position != pos) { update(); }
  this->position = pos;
}

Vec2<> Node::getPosition() const { return position; }

Vec2<> Node::getGlobalPosition() const {
  Vec2<> accumulator;
  const Node* n = this;
  while (n) {
    accumulator += n->position;
    n = n->getParent();
  }
  return accumulator;
}

void Node::update() { needUpdate = true; }
void Node::updateAll() {
  auto& children = getChildren();
  update();
  for (auto it = children.begin(); it != children.end(); ++it) {
    auto n = &it->get();
    n->updateAll();
  }
}

bool Node::willUpdate() const { return needUpdate; }

void Node::setGFX(GFX* gfx) { this->gfx = gfx; update(); }
GFX* Node::getGFX() const { return gfx; }
GFX* Node::getGFXTree() const {
  GFX* gfx = nullptr;
  const Node* n = this;
  while (!gfx && n) {
    gfx = n->getGFX();
    n = n->getParent();
  }
  return gfx;
}
