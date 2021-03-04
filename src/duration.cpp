#include "duration.h"
#include <algorithm>
#include <stdio.h>

#ifdef _WIN32
#define snprintf sprintf_s
#endif

Duration::Duration(Node* parent, int time) : Text(parent, "")
{
  setTime(time);
}

Duration::Duration(int time) : Duration(NULL, time) {}

void Duration::setTime(int time) {
  if (this->time != time) update();
  this->time = time;

  // truncate to 9:59:59
  time = std::min(time, 10 * 60 * 60 - 1);

  int sec = time % 60;
  int min = (time / 60) % 60;
  int hour = time / 60 / 60;

  int k = 0;
  if (hour > 0) k = snprintf(display, sizeof(display), "%01d:", hour);
  snprintf(display + k, sizeof(display) - k, "%02d:%02d", min, sec);
  setText(display);
}

int Duration::getTime() const { return this->time; }
