#pragma once
#include "text.h"

#ifndef IAR_COMPILER
#include <string>
#endif

class Marquee : public Text {
  protected:
    uint32_t delta = 0;
    uint32_t offset = 0;
    uint32_t delay = 1000;
    bool smooth = true;
    uint32_t speed = 20;
  public:
    Marquee(Node* parent = nullptr, const char* text = "Marquee");
    Marquee(const char* text);

    void setDelay(uint32_t);
    uint32_t getDelay() const;

    void setSmooth(bool);
    bool getSmooth() const;

    void setSpeed(uint32_t);
    uint32_t getSpeed() const;

    void draw();
    void process(uint32_t ms) override;

    void setDebugColor(Color);
    Color getDebugColor() const;

  private:
    Color debug_color = Colors::black;
    int32_t delay_countdown = delay;
    Vec2<> last_pos = {};
    std::string last_display;
};
