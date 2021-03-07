#include "mp3.h"
#include "texturebutton.h"
#include <pgm.h>
#include <assert.h>
#include <SDL_image.h>

namespace Colors {
  static const Color magenta{ 0xFF, 0x00, 0xFF };
}

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

Bitmap loadBitmap(const char* filename) {
  static bool initialized = false;
  if (!initialized) {
    uint32_t flags = IMG_INIT_PNG;
    if (!IMG_Init(flags)) { fprintf(stderr, "Failed to initialize SDL_image: %s\n", IMG_GetError()); exit(1); }
    initialized = true;
  }

  Bitmap out;
  auto surface = IMG_Load(filename);
  if (surface == NULL) {
    fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
    exit(1);
  }

  IMG_LoadPNM_RW(nullptr);
  
  uint32_t x = surface->w;
  uint32_t y = surface->h;
  printf("Opened %s (%d,%d)\n", filename, x, y);

  uint8_t *data = new uint8_t[x*y];

  SDL_ConvertPixels(x, y,
      // source info
      surface->format->format,
      surface->pixels,
      surface->pitch,
      // destination info
      SDL_PIXELFORMAT_INDEX8,
      data,
      x
      );

  out.setBitmap(data, { x,y });
  out.setColor(Colors::white);

  return out;
}

Bitmap play_texture = loadBitmap("play.png");
Bitmap pause_texture = loadBitmap("pause.png");
Bitmap next_texture = loadBitmap("next.png");
Bitmap prev_texture = loadBitmap("prev.png");

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
  printf("%s\n", __PRETTY_FUNCTION__);
  title.setTextSize(2);

  short x = getSize().x;
  short y = getSize().y;
  Vec2<> center{
    static_cast<int16_t>(x/2),
      static_cast<int16_t>(y/2)
  };

  controls.setSize({ x, 64 });
  playback.setSize({ x, 8 });

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
