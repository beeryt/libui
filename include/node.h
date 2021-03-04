#pragma once
#include "event.h"
#include <functional>
#include <vector>


class Node {
  private:
    using NodeList = std::vector<std::reference_wrapper<Node>>;
    Node* parent;
    NodeList children;
    bool processEnabled = true;
    bool inputEnabled = true;

  protected:
    virtual void _process();
    virtual bool _input(Event);

  public:
    Node(Node* parent = nullptr);
    virtual ~Node();

    Node* getParent() const;
    const NodeList& getChildren() const;

    void addChild(Node& child);
    void removeChild(Node& child);

    void setProcess(bool enable);
    void setInput(bool enable);
    bool isProcessEnabled() const;
    bool isInputEnabled() const;

    // Attempts to update this node and its children
    virtual void process();
    // Attempts to handle input for this node and its children
    virtual bool input(Event);
};
