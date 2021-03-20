#pragma once
#include "modes.h"

namespace modes {

  class TimezoneSetting: public Mode {
    bool select_minute = false;
    bool editing = false;

    int32_t edited_time_offset = 0;;

    public:
      TimezoneSetting();
      void tick();
  };

}