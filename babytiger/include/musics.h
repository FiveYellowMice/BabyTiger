#pragma once
#include "stdint.h"
#include "avr/pgmspace.h"

struct music_note {
  int16_t pitch;
  float duration;
};

namespace musics {
  extern const struct music_note senbonzakura[] PROGMEM;
  extern const struct music_note katyusha[] PROGMEM;
}

class MusicPlayer {
    uint16_t whole_note_length;
    const struct music_note *music;

    const struct music_note *current_note_ptr;
    bool started = false;
    bool note_playing = false;
    bool stopped = false;
    unsigned long last_update = 0;
    unsigned long next_update_in = 0;

  public:
    MusicPlayer(const struct music_note *new_music, uint16 new_whole_note_length);
    ~MusicPlayer();
    void tick();
    void stop();
    void reset();
    bool getStopped();
    unsigned long getLastUpdate();
};