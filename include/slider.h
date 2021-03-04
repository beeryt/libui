#pragma once
#include "canvas.h"
#include "color.h"

class Slider : public Canvas {
  private:
    int value, min, max;
    float percent;
    void setPercent();
    Color fg = Colors::white;
    Color bg = Colors::black;
  public:
    Slider(Node* parent = nullptr);
    void draw();

    void setVal(int);
    void setMin(int);
    void setMax(int);

    int getVal() const;
    int getMin() const;
    int getMax() const;
};
