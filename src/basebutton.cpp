#include "basebutton.h"

BaseButton::BaseButton(Node* parent) : Canvas(parent), onClick([](){}) {}

void BaseButton::setOnClick(OnClickHandler onClick) { this->onClick = onClick; }
const BaseButton::OnClickHandler& BaseButton::getOnClick() const { return onClick; }

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
  setInput(false);
  if (enabled) modeChanged();
  enabled = false;
}

void BaseButton::enable() {
  setInput(true);
  if (!enabled) modeChanged();
  enabled = true;
}

bool BaseButton::isEnabled() const {
  return enabled;
}

bool BaseButton::_input(Event e) {
  // TODO Consider adding mini state machine to track the
  // PRESS/RELEASE lifecycle. Also consider behaviors where a
  // press originates outside and ends inside and vice-versa.
  if (enabled && hasPoint(e.position)) {
    switch (e.type) {
      case Event::TOUCH:
        setMode(ButtonMode::PRESSED);
        return true;

      case Event::RELEASE:
        setMode(ButtonMode::NORMAL);
        onClick();
        return true;

      default: return false;
    }
  }
  return false;
}
