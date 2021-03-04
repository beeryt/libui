#pragma once
#include "basebutton.h"
#include "text.h"

class Button : public BaseButton {
  public:
    Button(Node* parent = NULL);

    Text& text = m_text;

  private:
    Text m_text;
};
