#include <Arduino.h>
#include "selection_menu.h"
#include "display.h"
#include "fonts.h"
#include "texts.h"
#include "rtc.h"
#include "mode_settings.h"
#include "mode_time_setting.h"

#define BCD_UINT8(x) ((((x) / 10) << 4) | ((x) % 10))

namespace modes {

  TimeSetting::TimeSetting() {
    selection = TimeSettingSelection::HOUR;
  }

  void TimeSetting::tick() {
    RtcDateTime clock_time = Rtc.GetDateTime();

    uint8_t current_clock_value;
    uint8_t value_min = 0;
    uint8_t value_max = 59;
    int8_t cursor_x = 0;
    int8_t cursor_y = 0;

    uint8_t *displayed_value = editing ? &edited_value : &current_clock_value;
    char text_buffer[11];

    switch (selection) {

      case TimeSettingSelection::YEAR:
        current_clock_value = clock_time.Year() - 2000;
        value_min = 0; // counting from year 2000
        value_max = 99;
        cursor_x = 9;
        cursor_y = 6;

        sprintf_P(text_buffer, PSTR("20%02d"), *displayed_value);
        draw_text(text_buffer, fonts::digits5, COLOR_CYAN, 1, 6);
        break;

      case TimeSettingSelection::MONTH:
        current_clock_value = clock_time.Month();
        value_min = 1;
        value_max = 12;
        cursor_x = 9;
        cursor_y = 9;

        strcpy_P(text_buffer, (char *) pgm_read_ptr(texts::months + *displayed_value - 1));
        draw_text(text_buffer, fonts::ascii7, COLOR_TENDER_GREEN, 0, 0);
        sprintf(text_buffer, "%02d", clock_time.Day());
        draw_text(text_buffer, fonts::digits5, COLOR_GREEN, 0, 9);
        sprintf(text_buffer, "%02d", *displayed_value);
        draw_text(text_buffer, fonts::digits5, COLOR_TENDER_GREEN, 9, 9);
        draw_text("/", fonts::digits5, COLOR_PURPLE, 7, 9);
        break;

      case TimeSettingSelection::DAY:
        current_clock_value = clock_time.Day();
        value_min = 1;
        switch (clock_time.Month()) {
          case 1:
          case 3:
          case 5:
          case 7:
          case 8:
          case 10:
          case 12:
            value_max = 31;
            break;
          case 2:
            if (clock_time.Year() % 100 == 0 ? clock_time.Year() % 400 == 0 : clock_time.Year() % 4 == 0) { // Leap year
              value_max = 29;
            } else {
              value_max = 28;
            }
            break;
          default:
            value_max = 30;
        }
        cursor_x = 0;
        cursor_y = 9;

        sprintf(text_buffer, "%02d", *displayed_value);
        draw_text(text_buffer, fonts::digits5, COLOR_GREEN, 0, 9);
        sprintf(text_buffer, "%02d", clock_time.Month());
        draw_text(text_buffer, fonts::digits5, COLOR_TENDER_GREEN, 9, 9);
        draw_text("/", fonts::digits5, COLOR_PURPLE, 7, 9);
        break;

      case TimeSettingSelection::HOUR:
        current_clock_value = clock_time.Hour();
        value_max = 23;
        cursor_x = 0;
        cursor_y = 2;

        sprintf(text_buffer, "%02d", *displayed_value);
        draw_text(text_buffer, fonts::digits5, COLOR_RED, 0, 2);
        sprintf(text_buffer, "%02d", clock_time.Minute());
        draw_text(text_buffer, fonts::digits5, COLOR_ORANGE, 8, 2);
        if (clock_time.Second() % 2) {
          draw_text(":", fonts::digits5, COLOR_GRAY, 7, 2);
        }
        break;

      case TimeSettingSelection::MINUTE:
        current_clock_value = clock_time.Minute();
        cursor_x = 8;
        cursor_y = 2;

        sprintf(text_buffer, "%02d", clock_time.Hour());
        draw_text(text_buffer, fonts::digits5, COLOR_RED, 0, 2);
        sprintf(text_buffer, "%02d", *displayed_value);
        draw_text(text_buffer, fonts::digits5, COLOR_ORANGE, 8, 2);
        if (clock_time.Second() % 2) {
          draw_text(":", fonts::digits5, COLOR_GRAY, 7, 2);
        }
        break;

      case TimeSettingSelection::SECOND:
        current_clock_value = clock_time.Second();
        cursor_x = 9;
        cursor_y = 9;

        sprintf(text_buffer, "%02d", clock_time.Hour());
        draw_text(text_buffer, fonts::digits5, COLOR_RED, 0, 2);
        sprintf(text_buffer, "%02d", clock_time.Minute());
        draw_text(text_buffer, fonts::digits5, COLOR_ORANGE, 8, 2);
        sprintf(text_buffer, "%02d", *displayed_value);
        draw_text(text_buffer, fonts::digits5, COLOR_YELLOW, 9, 9);
        if (clock_time.Second() % 2) {
          draw_text(":", fonts::digits5, COLOR_GRAY, 7, 2);
          draw_text(":", fonts::digits5, COLOR_YELLOW, 7, 9);
        }
        break;
    }

    if (!editing) {
      for (unsigned int i = 0; i < 7; i++) {
        set_pixel(cursor_x + i, cursor_y + 5, COLOR_WHITE);
      }

      button_event_handle(BTN_X, [&] {
        transition_mode(new modes::Settings(SettingsMenuSelection::TIME));
      });
      button_event_handle(BTN_O, [&] {
        editing = true;
        edited_value = current_clock_value;
      });
      selection_menu_handle_lr_button(&selection, [&] {});

    } else {
      draw_glyph(&fonts::triangle_up, COLOR_WHITE, cursor_x + 2, cursor_y - 2);
      draw_glyph(&fonts::triangle_down, COLOR_WHITE, cursor_x + 2, cursor_y + 5);

      button_event_handle(BTN_X, [&] {
        editing = false;
      });
      button_event_handle(BTN_O, [&] {
        editing = false;
        RtcDateTime new_time(
          selection == TimeSettingSelection::YEAR   ? 2000 + edited_value : clock_time.Year(),
          selection == TimeSettingSelection::MONTH  ? edited_value        : clock_time.Month(),
          selection == TimeSettingSelection::DAY    ? edited_value        : clock_time.Day(),
          selection == TimeSettingSelection::HOUR   ? edited_value        : clock_time.Hour(),
          selection == TimeSettingSelection::MINUTE ? edited_value        : clock_time.Minute(),
          selection == TimeSettingSelection::SECOND ? edited_value        : clock_time.Second()
        );
        Rtc.SetDateTime(new_time);
      });
      button_event_handle(BTN_L, [&] {
        if (edited_value == value_min) {
          edited_value = value_max;
        } else {
          edited_value--;
        }
      });
      button_event_handle(BTN_R, [&] {
        if (edited_value == value_max) {
          edited_value = value_min;
        } else {
          edited_value++;
        }
      });
    }

    display();
    clear_pixels();
  }

}