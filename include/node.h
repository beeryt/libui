#pragma once
#include "event.h"
#include "Adafruit_GFX.h"
#include <vector>
#include <functional>

using GFX = Adafruit_GFX;

class Node {
  private:
    using NodeList = std::vector<std::reference_wrapper<Node>>;
    Node* parent;
    NodeList children;

  protected:
    virtual void _process(uint32_t ms);
    virtual bool _input(Event);
    bool needUpdate = true;       //! indicates whether this node needs to process
    Vec2<> position;              //! position relative to parent
    GFX* gfx = nullptr;           //! A graphics object for drawing to

  public:
    Node(Node* parent = nullptr);
    virtual ~Node();

    Node* getParent() const;
    const NodeList& getChildren() const;

    void addChild(Node& child);
    void removeChild(Node& child);

    void setPosition(Vec2<>);
    Vec2<> getPosition() const;
    Vec2<> getGlobalPosition() const;

    void update();                //! request draw call on next frame
    void updateAll();             //! request draw call for this and all children
    bool willUpdate() const;      //! whether a draw call was requested

    // note: The Canvas::draw* calls use a GFX object to draw.
    // If getGFX() would return NULL, getGFXTree() would search
    // the parent nodes. You can use the getGFXTree() method to
    // determine what GFX object (if any) is active for this
    // node. If no parent has GFX set, then the Canvas::draw*
    // calls will silently return.
    void setGFX(GFX* gfx);        //! sets the active GFX for this node
    GFX* getGFX() const;          //! returns this node's internal GFX object
    GFX* getGFXTree() const;      //! returns the active GFX for this node

    // Attempts to update this node and its children
    virtual void process(uint32_t ms = 0);
    // Attempts to handle input for this node and its children
    virtual bool input(Event);
};
