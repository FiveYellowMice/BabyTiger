#pragma once
#include "modes.h"

namespace modes {

  enum class TimeSettingSelection {
    YEAR,
    MONTH,
    DAY,
    HOUR,
    MINUTE,
    SECOND,
    END = SECOND,
  };

  class TimeSetting: public Mode {
      TimeSettingSelection selection;
      bool editing = false;
      uint8_t edited_value = 1;
    
    public:
      TimeSetting();
      void tick();
  };

}