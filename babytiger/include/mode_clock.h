#pragma once
#include "modes.h"
#include "scroll_text.h"

namespace modes {

  class Clock: public Mode {
      unsigned long last_button_press = 0;
      uint8_t weather_page = 0;
      ScrollingText year_scroll;

    public:
      Clock();
      void tick();
  };

}