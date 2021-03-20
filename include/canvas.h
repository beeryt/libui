#pragma once
#include "node.h"
#include "vec2.hpp"
#include "rect.h"
#include "color.h"
#include "bitmap.h"

class Canvas : public Node {
  private:
    bool visible = true;          //! indicates visibility in the ui tree
    Vec2<> size;                  //! size of canvas

  protected:
    void _process(uint32_t ms) override;

  public:
    Canvas(Node* parent = NULL);
    void show();                  //! show this Canvas element
    void hide();                  //! hide this Canvas element
    bool isVisible() const;

    void setSize(Vec2<>);
    Vec2<> getSize() const;

    Rect<> getRect() const;
    virtual bool hasPoint(Vec2<> point) const;

    virtual void draw();          //! abstract implementation to draw the canvas item

    void drawPixel(Vec2<int16_t> position, Color color);
    void drawLine(Vec2<int16_t> position, Vec2<> line, Color color);
    void drawRect(Vec2<int16_t> position, Vec2<int16_t> size, Color border);
    void drawRect(Rect<int16_t> rect, Color border);
    void fillRect(Vec2<int16_t> position, Vec2<int16_t> size, Color fill);
    void fillRect(Rect<int16_t> rect, Color fill);
    void drawCircle(Vec2<int16_t> position, uint16_t radius, Color color, Color fill);
    void drawBitmap(Vec2<int16_t> position, Bitmap bitmap);
    void drawBitmapScaled(Vec2<int16_t> position, Bitmap bitmap, uint8_t scale);
    void drawChar(Vec2<int16_t> position, char c, Color color, Color bg, uint8_t size);
    void drawText(Vec2<int16_t> position, const char* text, Color color, Color bg, uint8_t size);

    void process(uint32_t ms = 0) override;
    bool input(Event) override;
};
