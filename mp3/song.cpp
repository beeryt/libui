#include "song.h"
#include <algorithm>
#include <random>

//#define DEBUG_SONGLIST
#ifdef DEBUG_SONGLIST
#include "print.h"
#endif

bool byTitle(const Song* a, const Song* b) {
  return a->info.title < b->info.title;
}

void SongList::add(Song* s) {
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

Song* SongList::prev() {
  if (it == songs.begin()) {
#ifdef DEBUG_SONGLIST
    char buf[32];
    PrintWithBuf(buf, sizeof(buf), "Skipping to end\n");
#endif
    it = songs.end();
  }
  return *it--;
}

Song* SongList::current() const { return *it; }

Song* SongList::next() {
  if ((it + 1) == songs.end()) {
#ifdef DEBUG_SONGLIST
    char buf[32];
    PrintWithBuf(buf, sizeof(buf), "Skipping to beginning\n");
#endif
    it = songs.begin();
  }
  return *it++;
}
