#pragma once
#include <stdint.h>
#include "modes.h"
#include "scroll_text.h"

namespace modes {

  enum class MainMenuSelection {
    ALARM,
    GAMES,
    SETTINGS,
    END = SETTINGS,
  };

  class MainMenu: public Mode {
      MainMenuSelection selection;
      ScrollingText title_scroll;
    public:
      MainMenu(MainMenuSelection designated_selection = MainMenuSelection::ALARM);
      void tick();
  };

}