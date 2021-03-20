#pragma once
#include "scroll_text.h"
#include "alarms.h"
#include "modes.h"

namespace modes {

  enum class AlarmSettingAlarmSelection {
    ALARM_1,
    ALARM_2,
    ALARM_3,
    END = ALARM_3,
  };

  enum class AlarmSettingSettingSelection {
    HOUR,
    MINUTE,
    ENABLED,
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    MUSIC,
    END = MUSIC,
  };

  class AlarmSetting: public Mode {
      AlarmSettingAlarmSelection alarm_selection;
      AlarmSettingSettingSelection setting_selection;
      bool alarm_chosen = false;
      bool editing = false;
      bool edited = false;
      struct alarm_config edited_alarm;
      uint8_t edited_numerical_value;
      AlarmMusicSelection edited_music;
      ScrollingText scroll;
      char scroll_text[14] = {'\0'};

    public:
      AlarmSetting();
      void tick();

    private:
      AlarmSlot currentAlarmSlot();
  };

}