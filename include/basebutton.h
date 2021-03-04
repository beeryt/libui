#pragma once
#include "text.h"
#include "canvas.h"
#include <functional>

enum class ButtonMode { NORMAL, PRESSED, DISABLED };

class BaseButton : public Canvas {
public:
  BaseButton(Node* parent = NULL);

  using OnClickHandler = std::function<void()>;
  void setOnClick(OnClickHandler onClick);
  const OnClickHandler& getOnClick() const;

  ButtonMode getMode() const;

  void setToggleMode(bool);
  bool isToggleMode() const;

  bool isPressed() const;

  void disable();
  void enable();
  bool isEnabled() const;

protected:
  bool _input(Event e);
  void setMode(ButtonMode mode);
  virtual void modeChanged();

private:
  std::function<void()> onClick;
  ButtonMode mode = ButtonMode::NORMAL;
  bool enabled = true;
  bool toggleMode = false;
};
