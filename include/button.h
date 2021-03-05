#pragma once
#include "basebutton.h"
#include "text.h"

class Button : public BaseButton {
  public:
    Button(Node* parent = NULL);

    Text& text = m_text;
    bool hasPoint(Vec2<> p) const override;

    void setBackground(Color color);
    Color getBackground() const;

    void draw() override;

  private:
    Color bg;
    Text m_text;
};
