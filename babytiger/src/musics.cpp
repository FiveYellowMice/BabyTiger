#include <Arduino.h>
#include "pins.h"
#include "music_scale.h"
#include "musics.h"

namespace musics {

  const struct music_note senbonzakura[] PROGMEM = {
    {NOTE_D4, 5.33},
    {NOTE_D4, 16},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},

    {NOTE_D4, 5.33},
    {NOTE_D4, 16},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_A3, 8},
    {NOTE_C4, 8},

    {NOTE_D4, 5.33},
    {NOTE_D4, 16},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},
    
    {NOTE_A4, 4},
    {NOTE_G4, 8},
    {NOTE_A4, 16},
    {NOTE_G4, 16},
    {NOTE_F4, 4},
    {NOTE_D4, 4},

    
    {NOTE_D4, 5.33},
    {NOTE_D4, 16},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},
    
    {NOTE_D4, 5.33},
    {NOTE_D4, 16},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_C4, 8},
    {NOTE_A3, 8},
    
    {NOTE_D4, 5.33},
    {NOTE_D4, 16},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},
    
    {NOTE_A4, 4},
    {NOTE_G4, 8},
    {NOTE_A4, 16},
    {NOTE_G4, 16},
    {NOTE_F4, 4},
    {NOTE_D4, 4},

    
    {NOTE_F4, 4},
    {NOTE_E4, 4},
    {NOTE_D4, 4},
    {NOTE_C4, 4},
    
    {NOTE_C4, 8},
    {NOTE_C4, 16},
    {NOTE_D4, 16},
    {NOTE_A3, 8},
    {NOTE_G3, 8},
    {NOTE_A3, 2},
    
    {NOTE_A3, 8},
    {NOTE_C4, 4},
    {NOTE_D4, 8},
    {NOTE_G4, 4},
    {NOTE_E4, 4},

    {NOTE_F4, 5.33},
    {NOTE_F4, 16},
    {NOTE_E4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 2},

    
    {NOTE_F4, 4},
    {NOTE_E4, 4},
    {NOTE_D4, 4},
    {NOTE_C4, 4},
    
    {NOTE_C4, 8},
    {NOTE_C4, 16},
    {NOTE_D4, 16},
    {NOTE_A3, 8},
    {NOTE_G3, 8},
    {NOTE_A3, 4},
    {NOTE_A3, 8},
    {NOTE_C4, 8},
    
    {NOTE_D4, 8},
    {NOTE_D4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 4},
    {NOTE_G4, 4},
    
    {NOTE_E4, 1.33},
    {NOTE_D4, 8},
    {NOTE_F4, 8},

    
    {NOTE_G4, 8},
    {NOTE_G4, 16},
    {NOTE_G4, 16},
    {NOTE_G4, 8},
    {NOTE_A4, 8},
    {NOTE_A4, 2.66},
    {NOTE_A4, 8},
    
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_A4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    
    {NOTE_G4, 8},
    {NOTE_G4, 16},
    {NOTE_G4, 16},
    {NOTE_G4, 8},
    {NOTE_A4, 8},
    {NOTE_A4, 2.66},
    {NOTE_A4, 8},
    
    {NOTE_AS4, 8},
    {NOTE_A4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 8},

    
    {NOTE_G4, 8},
    {NOTE_G4, 16},
    {NOTE_G4, 16},
    {NOTE_G4, 8},
    {NOTE_A4, 8},
    {NOTE_A4, 2.66},
    {NOTE_A4, 8},
    
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_A4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    
    {NOTE_AS4, 4},
    {NOTE_A4, 4},
    {NOTE_G4, 4},
    {NOTE_F4, 4},
    
    {NOTE_G4, 8},
    {NOTE_A4, 8},
    {NOTE_F4, 8},
    {NOTE_C4, 8},
    {NOTE_D4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    
    
    {NOTE_G4, 8},
    {NOTE_G4, 16},
    {NOTE_G4, 16},
    {NOTE_G4, 8},
    {NOTE_A4, 8},
    {NOTE_A4, 2.66},
    {NOTE_A4, 8},
    
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_A4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    
    {NOTE_G4, 8},
    {NOTE_G4, 16},
    {NOTE_G4, 16},
    {NOTE_G4, 8},
    {NOTE_A4, 8},
    {NOTE_A4, 2.66},
    {NOTE_A4, 8},
    
    {NOTE_AS4, 8},
    {NOTE_A4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 8},

    
    {NOTE_G4, 8},
    {NOTE_G4, 16},
    {NOTE_G4, 16},
    {NOTE_G4, 8},
    {NOTE_A4, 8},
    {NOTE_A4, 2.66},
    {NOTE_A4, 8},
    
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_A4, 4},
    {NOTE_D4, 8},
    {NOTE_F4, 8},
    
    {NOTE_AS4, 4},
    {NOTE_A4, 4},
    {NOTE_G4, 4},
    {NOTE_F4, 4},
    
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_A4, 8},
    {NOTE_C5, 8},
    {NOTE_D5, 2},
    
    {NOTE_MUSIC_END, 0},
  };

  const struct music_note katyusha[] PROGMEM = {
    {NOTE_A3, 2.66},
    {NOTE_B3, 8},
    {NOTE_C4, 2.66},
    {NOTE_A3, 8},
    {NOTE_C4, 8},
    {NOTE_C4, 8},
    {NOTE_B3, 8},
    {NOTE_A3, 8},
    {NOTE_B3, 4},
    {NOTE_E3, 4},

    {NOTE_B3, 2.66},
    {NOTE_C4, 8},
    {NOTE_D4, 2.66},
    {NOTE_B3, 8},
    {NOTE_D4, 8},
    {NOTE_D4, 8},
    {NOTE_C4, 8},
    {NOTE_B3, 8},
    {NOTE_A3, 2},

    {NOTE_E4, 4},
    {NOTE_A4, 4},
    {NOTE_G4, 4},
    {NOTE_A4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 8},
    {NOTE_E4, 8},
    {NOTE_D4, 8},
    {NOTE_E4, 4},
    {NOTE_A3, 4},

    {NOTE_F4, 2.66},
    {NOTE_D4, 8},
    {NOTE_E4, 2.66},
    {NOTE_C4, 8},
    {NOTE_B3, 8},
    {NOTE_E3, 8},
    {NOTE_C4, 8},
    {NOTE_B3, 8},
    {NOTE_A3, 2},

    {NOTE_E4, 4},
    {NOTE_A4, 4},
    {NOTE_G4, 4},
    {NOTE_A4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_F4, 8},
    {NOTE_E4, 8},
    {NOTE_D4, 8},
    {NOTE_E4, 4},
    {NOTE_A3, 4},

    {NOTE_F4, 2.66},
    {NOTE_D4, 8},
    {NOTE_E4, 2.66},
    {NOTE_C4, 8},
    {NOTE_B3, 8},
    {NOTE_E3, 8},
    {NOTE_C4, 8},
    {NOTE_B3, 8},
    {NOTE_A3, 2},

    {NOTE_MUSIC_END, 0},
  };

}

MusicPlayer::MusicPlayer(const struct music_note *new_music, uint16_t new_whole_note_length) {
  music = new_music;
  whole_note_length = new_whole_note_length;
  reset();
}

MusicPlayer::~MusicPlayer() {
  stop();
}

void MusicPlayer::tick() {
  if (stopped) return;

  unsigned long current_time = millis();
  if (!started) {
    last_update = current_time;
    next_update_in = 0;
    started = true;
  }

  if (current_time - last_update < next_update_in) return;

  last_update += next_update_in;

  struct music_note note_temp;
  memcpy_P(&note_temp, current_note_ptr, sizeof(struct music_note));
  uint16_t note_length = whole_note_length / note_temp.duration;

  if (!note_playing) {
    if (note_temp.pitch == NOTE_MUSIC_END) {
      stopped = true;
    } else if (note_temp.pitch == NOTE_REST) {
      // Rest
    } else {
      analogWriteFreq(note_temp.pitch);
      analogWrite(PIN_BUZZER, PWMRANGE / 2);
    }
    note_playing = true;
    next_update_in = note_length;
  } else {
    analogWrite(PIN_BUZZER, 0);
    note_playing = false;
    current_note_ptr++;
    next_update_in = note_length * 0.3;
  }
}

void MusicPlayer::stop() {
  analogWrite(PIN_BUZZER, 0);
  note_playing = false;
  stopped = true;
}

void MusicPlayer::reset() {
  current_note_ptr = music;
  started = false;
  note_playing = false;
  stopped = false;
}

bool MusicPlayer::getStopped() {
  return stopped;
}

unsigned long MusicPlayer::getLastUpdate() {
  return last_update;
}