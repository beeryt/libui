#pragma once
#include <vector>
#include <string>

struct Song {
  struct Info {
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
  };

  Info info;
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

