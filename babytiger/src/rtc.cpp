#include <Arduino.h>
#include <LittleFS.h>
#include "rtc.h"

RtcDS1307<TwoWire> Rtc(Wire);
int32_t time_offset = 0;

void time_init() {
  Rtc.Begin();
  Rtc.SetIsRunning(true);
  /*RtcDateTime compile_time(__DATE__, __TIME__);
  Rtc.SetDateTime(compile_time);*/

  time_offset = 0;
  File file = LittleFS.open("/time_offset.bin", "r");
  if (file) {
    for (uint8_t i = 0; i < 4; i++) {
      time_offset |= ((file.read() & 0xff) << (i * 8));
    }
    if (time_offset >= TIME_OFFSET_MIN && time_offset <= TIME_OFFSET_MAX) {
      Serial.printf_P(PSTR("[RTC] Read saved time offset: %d\n"), time_offset);
    } else {
      time_offset = 0;
    }
  }
}

RtcDateTime rtc_local_time() {
  return RtcDateTime(Rtc.GetDateTime().TotalSeconds() + time_offset);
}

bool set_time_offset(int32_t new_time_offset) {
  File file = LittleFS.open("/time_offset.bin", "w");
  if (!file) {
    Serial.printf_P(PSTR("[RTC] Filesystem open failed.\n"));
    return false;
  }
  for (uint8_t i = 0; i < 4; i++) {
    file.write((uint8_t) (new_time_offset >> (i * 8)));
  }
  file.close();
  time_offset = new_time_offset;
  return true;
}