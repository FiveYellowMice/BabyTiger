#pragma once
#include "musics.h"
#include "alarms.h"
#include "modes.h"

namespace modes {

  class FiringAlarm: public Mode {
      struct alarm_config alarm;
      MusicPlayer* player = nullptr;
      unsigned long player_stopped_millis = 0;
      unsigned long hold_start_millis = 0;
      bool held = false;

    public:
      FiringAlarm(AlarmSlot new_alarm_slot);
      ~FiringAlarm();
      void tick();
  };

}