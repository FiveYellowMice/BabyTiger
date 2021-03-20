#pragma once
#include "musics.h"
#include "modes.h"

namespace modes {

  class Games: public Mode {
      MusicPlayer music_player;

    public:
      Games();
      void tick();
  };

}