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

void Node::setProcess(bool enable) { processEnabled = enable; }
bool Node::isProcessEnabled() const { return processEnabled; }

void Node::setInput(bool enable) { inputEnabled = enable; }
bool Node::isInputEnabled() const { return inputEnabled; }

// process in pre-order so parents can update children first
void Node::process() {
  if (!processEnabled) return;
  _process();
  auto it = children.begin();
  while (it != children.end()) { (*it++).get().process(); }
}

// input is in post-order so children can handle input before parent
bool Node::input(Event event) {
  if (!inputEnabled) return false;
  for (auto it = children.begin(); it != children.end(); ++it) {
    auto& n = it->get();
    if (n.input(event)) return true;
  }
  return _input(event);
}

void Node::_process() {}
bool Node::_input(Event) {
  return false;
}
