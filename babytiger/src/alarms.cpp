#include <Arduino.h>
#include <LittleFS.h>
#include "rtc.h"
#include "alarms.h"

struct alarm_config the_alarms[ALARMS_COUNT] = {EMPTY_ALARM_CONFIG};
Timer the_timer;

#define ALARM_HAS_REPEATS(alarm) ( \
  (alarm).repeat_on_sunday || \
  (alarm).repeat_on_monday || \
  (alarm).repeat_on_tuesday || \
  (alarm).repeat_on_wednesday || \
  (alarm).repeat_on_thursday || \
  (alarm).repeat_on_friday || \
  (alarm).repeat_on_saturday \
)

void alarms_init() {
  for (uint8_t i = 0; i < ALARMS_COUNT; i++) {
    char file_path[14];
    snprintf_P(file_path, sizeof(file_path), PSTR("/alarms/%d.bin"), i);
    File file = LittleFS.open(file_path, "r");
    if (file) {
      file.read((uint8_t*) (the_alarms + i), sizeof(struct alarm_config));
      if (validate_alarm(the_alarms[i])) {
        Serial.printf_P(PSTR("[Alarms] Read saved alarm %d\n"), i);
      } else {
        the_alarms[i] = EMPTY_ALARM_CONFIG;
      }
    }
  }
}

// If this function is not called within the 1 minuite timeframe that the alarms is configured to fire at, the alarm will be missed.
// An alarm with lower number has higher priority.
AlarmSlot check_alarms() {
  for (uint8_t i = 0; i < ALARMS_COUNT; i++) {
    if (!the_alarms[i].enabled) continue;

    RtcDateTime clock_time = rtc_local_time();

    bool repeat_today = false;
    switch (clock_time.DayOfWeek()) {
      case 0:
        repeat_today = the_alarms[i].repeat_on_sunday;
        break;
      case 1:
        repeat_today = the_alarms[i].repeat_on_monday;
        break;
      case 2:
        repeat_today = the_alarms[i].repeat_on_tuesday;
        break;
      case 3:
        repeat_today = the_alarms[i].repeat_on_wednesday;
        break;
      case 4:
        repeat_today = the_alarms[i].repeat_on_thursday;
        break;
      case 5:
        repeat_today = the_alarms[i].repeat_on_friday;
        break;
      case 6:
        repeat_today = the_alarms[i].repeat_on_saturday;
        break;
    }
    if (!repeat_today) {
      // If there are any repeats configured, that means the alarm is supposed to be repeated, and since it's not repeated today, we don't fire it
      // But, if there are no repeats configured, that means we are supposed to fire it just this once
      if (ALARM_HAS_REPEATS(the_alarms[i])) continue;
    }

    if (clock_time.Hour() != the_alarms[i].hour || clock_time.Minute() != the_alarms[i].minute) continue;

    if (millis() - the_alarms[i].last_update_millis < 60000) continue; // it has just been fired

    return ALARM_SLOT_FROM_I(i);
  }

  return AlarmSlot::NONE;
}

void fire_alarm(AlarmSlot slot) {
  if (slot == AlarmSlot::NONE) return;

  if (!ALARM_HAS_REPEATS(the_alarms[ALARM_SLOT_TO_I(slot)])) {
    // Disable oneshot alarm
    the_alarms[ALARM_SLOT_TO_I(slot)].enabled = false;
  }
  the_alarms[ALARM_SLOT_TO_I(slot)].last_update_millis = millis();
}

struct alarm_config get_alarm(AlarmSlot slot) {
  if (slot == AlarmSlot::NONE) return EMPTY_ALARM_CONFIG;
  return the_alarms[ALARM_SLOT_TO_I(slot)];
}

bool set_alarm(AlarmSlot slot, struct alarm_config config) {
  if (slot == AlarmSlot::NONE) return false;
  if (!validate_alarm(config)) return false;
  config.last_update_millis = millis();

  char file_path[14];
  snprintf_P(file_path, sizeof(file_path), PSTR("/alarms/%d.bin"), ALARM_SLOT_TO_I(slot));
  File file = LittleFS.open(file_path, "w");
  if (!file) {
    Serial.printf_P(PSTR("[Alarms] Filesystem open failed.\n"));
    return false;
  }
  Serial.printf_P(PSTR("[Alarms] Alarm %d saved: %d bytes written\n"),
    ALARM_SLOT_TO_I(slot),
    file.write((uint8_t*) &config, sizeof(struct alarm_config)));
  file.close();
  the_alarms[ALARM_SLOT_TO_I(slot)] = config;
  return true;
}

bool validate_alarm(struct alarm_config config) {
  return
    config.hour <= 23 &&
    config.minute <= 59 &&
    config.music >= AlarmMusicSelection::NONE &&
    config.music <= AlarmMusicSelection::END;
}