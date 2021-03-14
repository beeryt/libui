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

// Handles printf "%02d" since using tiny printf is lacking
size_t mysnprintf(char* buf, size_t size, uint8_t value) {
  auto k = snprintf(buf, size, "%d", (value / 10) % 10);
  k += snprintf(buf+k, size-k, "%d", value % 10);
  return k;
}

void Duration::setTime(int time) {
  if (this->time != time) update();
  this->time = time;

  // truncate to 9:59:59
  time = std::min(time, 10 * 60 * 60 - 1);

  int sec = time % 60;
  int min = (time / 60) % 60;
  int hour = time / 60 / 60;

  int k = 0;
  if (hour > 0) k = snprintf(display, sizeof(display), "%d", hour);
  k += mysnprintf(display + k, sizeof(display) - k, min);
  k += snprintf(display + k, sizeof(display) - k, ":");
  k += mysnprintf(display + k, sizeof(display) - k, sec);
  setText(display);
}

int Duration::getTime() const { return this->time; }
