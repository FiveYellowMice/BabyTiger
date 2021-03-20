#pragma once
#include "modes.h"
#include "selection_menu.h"
#include "scroll_text.h"

namespace modes {

  enum class SettingsMenuSelection {
    TIME,
    TIMEZONE,
    NTP,
    WIFI,
    END = WIFI,
  };

  class Settings: public Mode {
      SettingsMenuSelection selection;
      ScrollingText title_scroll;
      char detail_text[31] = {'\0'};
      ScrollingText detail_scroll;

    public:
      Settings(SettingsMenuSelection designated_selection = SettingsMenuSelection::TIME);
      void tick();
  };

}