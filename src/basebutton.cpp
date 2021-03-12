#include "basebutton.h"

BaseButton::BaseButton(Node* parent) : Canvas(parent), onClick([](){}) {}

void BaseButton::setOnClick(OnClickHandler onClick) { this->onClick = onClick; }
const BaseButton::OnClickHandler& BaseButton::getOnClick() const { return onClick; }

bool BaseButton::isPressed() const { return pressed; }

void BaseButton::setMode(ButtonMode mode) {
  if (this->mode != mode) {
    this->mode = mode;
    modeChanged();
  }
}

void BaseButton::modeChanged() {}

ButtonMode BaseButton::getMode() const {
  if (!enabled) return ButtonMode::DISABLED;
  return mode;
}

void BaseButton::disable() {
  if (enabled) modeChanged();
  enabled = false;
}

void BaseButton::enable() {
  if (!enabled) modeChanged();
  enabled = true;
}

bool BaseButton::isEnabled() const {
  return enabled;
}

void BaseButton::setToggleMode(bool mode) { toggleMode = mode; }
bool BaseButton::getToggleMode() const { return toggleMode; }

bool BaseButton::_input(Event e) {
  if (!enabled) return false;
  // TODO Consider adding mini state machine to track the
  // PRESS/RELEASE lifecycle. Also consider behaviors where a
  // press originates outside and ends inside and vice-versa.
  if (hasPoint(e.position)) {
    bool handled = false;
    switch (e.type) {
      case Event::TOUCH:
        handled = true;
        pressed = toggleMode ? pressed : true;
        break;

      case Event::RELEASE:
        handled = true;
        pressed = toggleMode ? !pressed : false;
        onClick();
        break;

      default:
        handled = false;
        break;
    }
    setMode(pressed ? ButtonMode::PRESSED : ButtonMode::NORMAL);
    return handled;
  }
  return false;
}
