#include "mp3.h"
#include "texturebutton.h"
#include <assert.h>

class ColorRect : public Canvas {
  public:
    ColorRect(Node* parent, Color fg) : Canvas(parent), fg(fg) {}
    ColorRect(Color fg = Colors::white) : ColorRect(nullptr, fg) {}
    bool input(Event) { return true; }
    void draw() {
      drawRect(getGlobalPosition(), getSize(), fg, fg);
    }
  private:
    Color fg;
};

static const Color c = Colors::magenta * .25;

template <typename T>
T ntoh(T raw) {
  uint8_t* data = reinterpret_cast<uint8_t*>(&raw);
  T out = 0;
  int size = sizeof(T);
  for (int i = 0; i < size; ++i) {
    out |= ((T)data[size-i-1] << (i*8));
  }
  return out;
}

class Controls : public Canvas {
  public:
    TextureButton prev, play, next;
    Controls() :
 prev(prev_texture),
 play(play_texture, pause_texture),
 next(next_texture) {
      addChild(prev);
      addChild(next);
      addChild(play);
      prev.setSize({ 48,48 });
      next.setSize({ 48,48 });
      play.setSize({ 64,64 });

      short voffset = (play.getSize().y - next.getSize().y) / 2;
      short center = 240 / 2;
      short hoffset = (center - prev.getSize().x - play.getSize().x/2)/2;
      prev.setPosition({ hoffset, voffset });
      next.setPosition({
          static_cast<int16_t>(center+hoffset+play.getSize().x/2),
          static_cast<int16_t>(voffset)
          });
      play.setPosition({
          static_cast<int16_t>(center-play.getSize().x/2),
          static_cast<int16_t>(0)
          });
    }
};

MP3::MP3(short x, short y) {
  addChild(title);
  addChild(artist);
  addChild(playback);
  addChild(controls);
  static Controls hack;
  controls.addChild(hack);
  setSize({ x,y });

  refreshLayout();
}

void MP3::refreshLayout() {
  printf("%s\n", __FUNCTION__);
  title.setTextSize(3);
  artist.setTextSize(2);
  artist.setSpeed(30);

  short x = getSize().x;
  short y = getSize().y;
  Vec2<> center{
    static_cast<int16_t>(x/2),
      static_cast<int16_t>(y/2)
  };

  title.setSize({ x - 64, title.getSize().y });
  artist.setSize({ x - 64, title.getSize().y });
  controls.setSize({ x, 64 });
  playback.setSize({ x, 8 });


  title.setDebug(true);
  artist.setDebug(true);
  title.setPosition(Vec2<>{
      static_cast<int16_t>(32),
      static_cast<int16_t>(center.y - title.getSize().y)
      });
  artist.setPosition(Vec2<>{
      static_cast<int16_t>(32),
      static_cast<int16_t>(center.y)
      });
  playback.setPosition(Vec2<>{
      static_cast<int16_t>(0),
      static_cast<int16_t>(y - playback.getSize().y - controls.getSize().y)
      });
  controls.setPosition({
      static_cast<int16_t>(0),
      static_cast<int16_t>(y - controls.getSize().y)
  });
}
