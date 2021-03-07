#include "mp3.h"
#include "SDL_image.h"

Bitmap play_texture = loadBitmap("play.png");
Bitmap pause_texture = loadBitmap("pause.png");
Bitmap next_texture = loadBitmap("next.png");
Bitmap prev_texture = loadBitmap("prev.png");

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
