#pragma once
#include "canvas.h"

class Text : public Canvas {
  private:
    const char* text;
    Color fg = Colors::white;
    Color bg = Colors::black;
    uint8_t size = 1;
  public:
    Text(Node* parent, const char* text);
    Text(Node* parent = nullptr);
    Text(const char* text);
    void draw();

    void setText(const char* text);
    const char* getText() const;

    void setColor(Color color);
    Color getColor() const;

    void setBackground(Color color);
    Color getBackground() const;

    void setTextSize(uint8_t size);
    uint8_t getTextSize() const;
};

