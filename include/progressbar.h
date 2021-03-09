#pragma once
#include "canvas.h"
#include "color.h"

class ProgressBar : public Canvas {
  private:
    int value, min, max;
    float percent;
    int16_t last_width = 0;
    void setPercent();
    Color fg = Colors::white;
    Color bg = Colors::black;
  public:
    ProgressBar(Node* parent = nullptr);
    void draw();

    void setVal(int);
    void setMin(int);
    void setMax(int);

    int getVal() const;
    int getMin() const;
    int getMax() const;
};
