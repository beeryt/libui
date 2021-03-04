#pragma once
#include "text.h"

class Duration : public Text {
  private:
    int time;
    char display[8]; // limited to H:MM:SS
  public:
    Duration(Node* parent, int time);
    Duration(int time = 0);

    void setTime(int time);
    int getTime() const;
};
