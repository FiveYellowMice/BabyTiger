#include <Arduino.h>
#include "buttons.h"
#include "display.h"
#include "fonts.h"
#include "rtc.h"
#include "mode_settings.h"
#include "mode_timezone_setting.h"

namespace modes {

  TimezoneSetting::TimezoneSetting() {}

  void TimezoneSetting::tick() {
    int32_t *displayed_offset = editing ? &edited_time_offset : &time_offset;

    char text_buffer[5];
    snprintf_P(text_buffer, sizeof(text_buffer), PSTR("UTC%c"), *displayed_offset < 0 ? '-' : '+');
    draw_text(text_buffer, fonts::digits5, COLOR_PURPLE, 1, 0);
    snprintf_P(text_buffer, sizeof(text_buffer), PSTR("%02d%02d"), abs(*displayed_offset) / 3600, (abs(*displayed_offset) / 60) % 60);
    draw_text(text_buffer, fonts::digits5, COLOR_PURPLE, 1, 7);
    draw_text(":", fonts::digits5, COLOR_GRAY, 8, 7);

    int8_t cursor_x = select_minute ? 9 : 1;

    if (!editing) {
      for (unsigned int i = 0; i < 7; i++) {
        set_pixel(cursor_x + i, 12, COLOR_WHITE);
      }

      button_event_handle(BTN_X, [&] {
        transition_mode(new modes::Settings(SettingsMenuSelection::TIMEZONE));
      });
      button_event_handle(BTN_O, [&] {
        editing = true;
        edited_time_offset = time_offset;
      });
      button_event_handle(BTN_L, [&] {
        select_minute = !select_minute;
      });
      button_event_handle(BTN_R, [&] {
        select_minute = !select_minute;
      });

    } else {
      draw_glyph(&fonts::triangle_up, COLOR_WHITE, cursor_x + 2, 5);
      draw_glyph(&fonts::triangle_down, COLOR_WHITE, cursor_x + 2, 12);

      button_event_handle(BTN_X, [&] {
        editing = false;
      });
      button_event_handle(BTN_O, [&] {
        editing = false;
        set_time_offset(edited_time_offset);
      });
      button_event_handle(BTN_L, [&] {
        edited_time_offset -= select_minute ? 15 * 60 : 60 * 60;
        if (edited_time_offset < TIME_OFFSET_MIN) {
          edited_time_offset = TIME_OFFSET_MAX;
        }
      });
      button_event_handle(BTN_R, [&] {
        edited_time_offset += select_minute ? 15 * 60 : 60 * 60;
        if (edited_time_offset > TIME_OFFSET_MAX) {
          edited_time_offset = TIME_OFFSET_MIN;
        }
      });
    }

    display();
    clear_pixels();
  }

}