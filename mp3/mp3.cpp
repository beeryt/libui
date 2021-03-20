#include "mp3.h"
#include "texturebutton.h"
#include <assert.h>

Controls::Controls() :
  prev(prev_texture),
  play(play_texture, pause_texture),
  next(next_texture)
{
  addChild(prev);
  addChild(play);
  addChild(next);

  play.setToggleMode(true);
  prev.setOnClick([](){});
  play.setOnClick([](){});
  next.setOnClick([](){});
}

void Controls::refreshLayout() {
  Vec2<short> smallerIconSize{ 48,48 };
  Vec2<short> largerIconSize{ 64,64 };

  prev.setSize(smallerIconSize);
  next.setSize(smallerIconSize);
  play.setSize(largerIconSize);

  short voffset = (play.getSize().y - next.getSize().y) / 4;
  short center = getSize().x / 2;
  short hoffset = (center - prev.getSize().x - play.getSize().x/2)/2;
  short x,y;

  x = hoffset;
  y = voffset;
  prev.setPosition({ x,y });

  x = center+hoffset+largerIconSize.x/2;
  y = voffset;
  next.setPosition({ x,y });

  x = center - largerIconSize.x/2;
  y = 0;
  play.setPosition({ x,y });
}

MP3::MP3(short x, short y) {
  addChild(title);
  addChild(artist);
  addChild(album);
  addChild(playback);
  addChild(controls);
  setSize({ x,y });

  refreshLayout();
}

void MP3::refreshLayout() {
  title.setTextSize(3);
  artist.setTextSize(2);
  album.setTextSize(2);
  title.setSpeed(50);
  artist.setSpeed(30);
  album.setSpeed(30);

  const auto size = getSize();
  const auto center = size / 2;
  short x = size.x;
  short y = size.y;

  const Vec2<short> songDetailPadding{ 24, 0 };

  x = size.x - 2 * songDetailPadding.x;
  y = 8*title.getTextSize();
  title.setSize({ x,y });

  y = 8*artist.getTextSize();
  artist.setSize({ x,y });

  y = 8*album.getTextSize();
  album.setSize({ x,y });

  x = size.x;
  y = play_texture.getSize().y;
  controls.setSize({ x,y });

  y = 8;
  playback.setSize({ x,y });

  x = songDetailPadding.x;
  y = center.y - title.getSize().y;
  title.setPosition(Vec2<>{ x,y });

  y = center.y;
  artist.setPosition(Vec2<>{ x,y });

  y = center.y + artist.getSize().y;
  album.setPosition(Vec2<>{ x,y });

  x = 0;
  y = size.y - playback.getSize().y - controls.getSize().y;
  playback.setPosition(Vec2<>{ x,y });

  y = size.y - controls.getSize().y;
  controls.setPosition({ x,y });

  controls.refreshLayout();
}
