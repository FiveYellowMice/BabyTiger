#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "musics.h"

enum class AlarmMusicSelection {
  NONE,
  SENBONZAKURA,
  KATYUSHA,
  END = KATYUSHA,
};

struct alarm_config {
  AlarmMusicSelection music;
  uint8_t hour;
  uint8_t minute;
  bool repeat_on_sunday : 1;
  bool repeat_on_monday : 1;
  bool repeat_on_tuesday : 1;
  bool repeat_on_wednesday : 1;
  bool repeat_on_thursday : 1;
  bool repeat_on_friday : 1;
  bool repeat_on_saturday : 1;
  bool enabled : 1;

  unsigned long last_update_millis;
};

#define EMPTY_ALARM_CONFIG {AlarmMusicSelection::NONE, 0, 0, false, false, false, false, false, false, false, false, 0}

#define ALARMS_COUNT 3

enum class AlarmSlot {
  NONE,
  ALARM_1,
  ALARM_2,
  ALARM_3,
};

#define ALARM_SLOT_TO_I(slot) (static_cast<uint8_t>(slot) - 1)
#define ALARM_SLOT_FROM_I(i) (static_cast<AlarmSlot>((i) + 1))

void alarms_init();
AlarmSlot check_alarms(); // return an alarm that should be fired
void fire_alarm(AlarmSlot slot); // mark the alarm to have been fired, does not actually invoke mode::FiringAlarm
struct alarm_config get_alarm(AlarmSlot slot);
bool set_alarm(AlarmSlot slot, struct alarm_config config);
bool validate_alarm(struct alarm_config config);

class Timer {
    unsigned long start_millis = 0;

  public:
    int32_t seconds = 0;
    
    bool check(); // return whether it should be fired
    int32_t remaining_seconds();
    void start();
    void stop();
};

extern Timer the_timer;