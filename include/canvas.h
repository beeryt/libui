#pragma once
#include "node.h"
#include "vec2.hpp"
#include "rect.h"
#include "color.h"
#include "bitmap.h"
#include "Adafruit_GFX.h"

using GFX = Adafruit_GFX;

class Canvas : public Node {
  private:
    bool visible = true;          //! indicates visibility in the ui tree
    bool needDraw = true;         //! indicates whether a new draw is necessary
    Vec2<> position;              //! position relative to parent
    Vec2<> size;                  //! size of canvas
    GFX* gfx = nullptr;           //! A graphics object for drawing to

  protected:
    void _process(uint32_t ms) override;

  public:
    Canvas(Node* parent = NULL);
    void show();                  //! show this Canvas element
    void hide();                  //! hide this Canvas element
    bool isVisible() const;

    void setSize(Vec2<>);
    Vec2<> getSize() const;

    void setPosition(Vec2<>);
    Vec2<> getPosition() const;
    Vec2<> getGlobalPosition() const;

    Rect<> getRect() const;
    virtual bool hasPoint(Vec2<> point) const;

    void update();                //! request draw call on next frame
    void updateAll();             //! request draw call for this and all children
    bool willDraw() const;        //! whether a draw call was requested

    virtual void draw();          //! abstract implementation to draw the canvas item

    // note: The Canvas::draw* calls use a GFX object to draw.
    // If getGFX() would return NULL, getGFXTree() would search
    // the parent nodes. You can use the getGFXTree() method to
    // determine what GFX object (if any) is active for this
    // node. If no parent has GFX set, then the Canvas::draw*
    // calls will silently return.

    void setGFX(GFX* gfx);        //! sets the active GFX for this node
    GFX* getGFX() const;          //! returns this node's internal GFX object
    GFX* getGFXTree() const;      //! returns the active GFX for this node

    void drawPixel(Vec2<int16_t> position, Color color);
    void drawLine(Vec2<int16_t> position, Vec2<> line, Color color);
    void drawRect(Vec2<int16_t> position, Vec2<int16_t> size, Color border, Color fill);
    void drawRect(Rect<int16_t> rect, Color border, Color fill);
    void drawCircle(Vec2<int16_t> position, uint16_t radius, Color color, Color fill);
    void drawBitmap(Vec2<int16_t> position, Bitmap bitmap);
    void drawChar(Vec2<int16_t> position, char c, Color color, Color bg, uint8_t size);
    void drawText(Vec2<int16_t> position, const char* text, Color color, Color bg, uint8_t size);

    void process(uint32_t ms = 0) override;
    bool input(Event) override;
};
