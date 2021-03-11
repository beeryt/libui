#include "song.h"
#include <algorithm>
#include <random>

bool byTitle(const Song& a, const Song& b) {
  return a.title < b.title;
}

void SongList::add(Song s) {
  songs.push_back(s);
  it = songs.begin();
}

void SongList::shuffle() {
  static std::random_device rd;
  static std::mt19937 g(rd());
  std::shuffle(songs.begin(), songs.end(), g);
}

void SongList::sort() {
  std::sort(songs.begin(), songs.end(), byTitle);
}

Song& SongList::prev() {
  if (it == songs.begin()) it = songs.end();
  return *it--;
}

Song& SongList::current() const { return *it; }

Song& SongList::next() {
  if (it == songs.end()) it = songs.begin();
  return *it++;
}
