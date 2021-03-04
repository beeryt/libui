#pragma once
#include "slider.h"
#include "duration.h"

class Playback : public Canvas {
private:
  Duration progress;
  Duration duration;
  Slider slider;
public:
  Playback(Node* parent = NULL, int duration = 0);
  Playback(int duration);
  void setProgress(int progress);
  void setDuration(int duration);
  int getProgress() const;
  int getDuration() const;
};
