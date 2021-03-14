#pragma once
#include <vector>
#include <string>

struct Song {
  std::string title, artist, album;
  std::string filename;
  int duration;
};

class SongList {
  public:
    void add(Song*);
    void shuffle();
    void sort(); // TODO add criteria

    const std::vector<Song*>& list = songs;

    Song* prev();
    Song* current() const;
    Song* next();

  private:
    std::vector<Song*> songs;
    std::vector<Song*>::iterator it = songs.begin();
};

