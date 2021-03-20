#include <Arduino.h>
#include "buttons.h"
#include "display.h"
#include "texts.h"
#include "fonts.h"
#include "images.h"
#include "selection_menu.h"
#include "mode_main_menu.h"
#include "mode_alarm_setting.h"

namespace modes {

  AlarmSetting::AlarmSetting() {
    alarm_selection = AlarmSettingAlarmSelection::ALARM_1;
    setting_selection = AlarmSettingSettingSelection::HOUR;
    scroll_text_init(
      &scroll,
      scroll_text, fonts::ascii7, COLOR_LAKE_BLUE,
      0, 9, SCROLL_TEXT_MODE_ADAPTIVE,
      800, 60
    );
  }

  void AlarmSetting::tick() {
    char text_buffer[3];

    if (!alarm_chosen) {
      int8_t display_offset = 0;
      int8_t selection_line_pos_y = 0;
      switch (alarm_selection) {
        case AlarmSettingAlarmSelection::ALARM_1:
          display_offset = 0;
          selection_line_pos_y = 5;
          break;
        case AlarmSettingAlarmSelection::ALARM_2:
          display_offset = 0;
          selection_line_pos_y = 11;
          break;
        case AlarmSettingAlarmSelection::ALARM_3:
          display_offset = -2;
          selection_line_pos_y = 17;
          break;
      }
      for (uint8_t i = 0; i < ALARMS_COUNT; i++) {
        struct alarm_config alarm = get_alarm(ALARM_SLOT_FROM_I(i));
        snprintf(text_buffer, sizeof(text_buffer), "%02d", alarm.hour);
        draw_text(text_buffer, fonts::digits5, alarm.enabled ? COLOR_GREEN : COLOR_RED, 0, 6 * i + display_offset);
        snprintf(text_buffer, sizeof(text_buffer), "%02d", alarm.minute);
        draw_text(text_buffer, fonts::digits5, alarm.enabled ? COLOR_GREEN : COLOR_RED, 8, 6 * i + display_offset);
        draw_text(":", fonts::digits5, COLOR_GRAY, 7, 6 * i + display_offset);
      }
      for (uint8_t i = 0; i < 16; i++) {
        set_pixel(i, selection_line_pos_y + display_offset, COLOR_WHITE);
      }

      button_event_handle(BTN_X, [&] {
        transition_mode(new modes::MainMenu(MainMenuSelection::ALARM));
      });
      button_event_handle(BTN_O, [&] {
        edited_alarm = get_alarm(currentAlarmSlot());
        alarm_chosen = true;
        setting_selection = AlarmSettingSettingSelection::HOUR;
      });
      selection_menu_handle_lr_button(&alarm_selection, [&] {});

    } else {
      switch (setting_selection) {

        case AlarmSettingSettingSelection::HOUR:
        case AlarmSettingSettingSelection::MINUTE:
        case AlarmSettingSettingSelection::ENABLED:
          snprintf(text_buffer, sizeof(text_buffer), "%02d",
            editing && setting_selection == AlarmSettingSettingSelection::HOUR ? edited_numerical_value : edited_alarm.hour);
          draw_text(text_buffer, fonts::digits5, COLOR_RED, 0, 2);
          snprintf(text_buffer, sizeof(text_buffer), "%02d",
            editing && setting_selection == AlarmSettingSettingSelection::MINUTE ? edited_numerical_value : edited_alarm.minute);
          draw_text(text_buffer, fonts::digits5, COLOR_ORANGE, 8, 2);
          draw_text(":", fonts::digits5, COLOR_GRAY, 7, 2);
          if (edited_alarm.enabled) {
            draw_text("On", fonts::ascii7, COLOR_GREEN, 0, 9);
          } else {
            draw_text("Off", fonts::ascii7, COLOR_RED, 0, 9);
          }

          switch (setting_selection) {
            case AlarmSettingSettingSelection::HOUR:
              if (editing) {
                draw_glyph(&fonts::triangle_up, COLOR_WHITE, 2, 0);
                draw_glyph(&fonts::triangle_down, COLOR_WHITE, 2, 7);
                button_event_handle(BTN_L, [&] {
                  if (edited_numerical_value == 0) {
                    edited_numerical_value = 23;
                  } else {
                    edited_numerical_value--;
                  }
                });
                button_event_handle(BTN_R, [&] {
                  if (edited_numerical_value == 23) {
                    edited_numerical_value = 0;
                  } else {
                    edited_numerical_value++;
                  }
                });
                button_event_handle(BTN_O, [&] {
                  editing = false;
                  edited = true;
                  edited_alarm.hour = edited_numerical_value;
                });
              } else {
                for (uint8_t i = 0; i < 7; i++) {
                  set_pixel(0 + i, 7, COLOR_WHITE);
                }
                button_event_handle(BTN_O, [&] {
                  editing = true;
                  edited_numerical_value = edited_alarm.hour;
                });
              }
              break;

            case AlarmSettingSettingSelection::MINUTE:
              if (editing) {
                draw_glyph(&fonts::triangle_up, COLOR_WHITE, 10, 0);
                draw_glyph(&fonts::triangle_down, COLOR_WHITE, 10, 7);
                button_event_handle(BTN_L, [&] {
                  if (edited_numerical_value == 0) {
                    edited_numerical_value = 59;
                  } else {
                    edited_numerical_value--;
                  }
                });
                button_event_handle(BTN_R, [&] {
                  if (edited_numerical_value == 59) {
                    edited_numerical_value = 0;
                  } else {
                    edited_numerical_value++;
                  }
                });
                button_event_handle(BTN_O, [&] {
                  editing = false;
                  edited = true;
                  edited_alarm.minute = edited_numerical_value;
                });
              } else {
                for (uint8_t i = 0; i < 7; i++) {
                  set_pixel(8 + i, 7, COLOR_WHITE);
                }
                button_event_handle(BTN_O, [&] {
                  editing = true;
                  edited_numerical_value = edited_alarm.minute;
                });
              }
              break;

            case AlarmSettingSettingSelection::ENABLED:
              for (uint8 i = 0; i < 16; i++) {
                set_pixel(i, 15, COLOR_WHITE);
              }
              button_event_handle(BTN_O, [&] {
                edited = true;
                edited_alarm.enabled = !edited_alarm.enabled;
              });
              break;

            default:
              ;
          }
          break;

        case AlarmSettingSettingSelection::SUNDAY:
        case AlarmSettingSettingSelection::MONDAY:
        case AlarmSettingSettingSelection::TUESDAY:
        case AlarmSettingSettingSelection::WEDNESDAY:
        case AlarmSettingSettingSelection::THURSDAY:
        case AlarmSettingSettingSelection::FRIDAY:
        case AlarmSettingSettingSelection::SATURDAY:
          draw_image(&images::repeat, 0, 0);
          set_pixel(2, 7, edited_alarm.repeat_on_sunday ? COLOR_GREEN : COLOR_RED);
          set_pixel(4, 7, edited_alarm.repeat_on_monday ? COLOR_GREEN : COLOR_RED);
          set_pixel(6, 7, edited_alarm.repeat_on_tuesday ? COLOR_GREEN : COLOR_RED);
          set_pixel(8, 7, edited_alarm.repeat_on_wednesday ? COLOR_GREEN : COLOR_RED);
          set_pixel(10, 7, edited_alarm.repeat_on_thursday ? COLOR_GREEN : COLOR_RED);
          set_pixel(12, 7, edited_alarm.repeat_on_friday ? COLOR_GREEN : COLOR_RED);
          set_pixel(14, 7, edited_alarm.repeat_on_saturday ? COLOR_GREEN : COLOR_RED);

          {
            int8_t day_of_week_num = 0;
            bool repeat_on_that_day = false;
            switch (setting_selection) {
              case AlarmSettingSettingSelection::SUNDAY:
                day_of_week_num = 0;
                repeat_on_that_day = edited_alarm.repeat_on_sunday;
                break;
              case AlarmSettingSettingSelection::MONDAY:
                day_of_week_num = 1;
                repeat_on_that_day = edited_alarm.repeat_on_monday;
                break;
              case AlarmSettingSettingSelection::TUESDAY:
                day_of_week_num = 2;
                repeat_on_that_day = edited_alarm.repeat_on_tuesday;
                break;
              case AlarmSettingSettingSelection::WEDNESDAY:
                day_of_week_num = 3;
                repeat_on_that_day = edited_alarm.repeat_on_wednesday;
                break;
              case AlarmSettingSettingSelection::THURSDAY:
                day_of_week_num = 4;
                repeat_on_that_day = edited_alarm.repeat_on_thursday;
                break;
              case AlarmSettingSettingSelection::FRIDAY:
                day_of_week_num = 5;
                repeat_on_that_day = edited_alarm.repeat_on_friday;
                break;
              case AlarmSettingSettingSelection::SATURDAY:
                day_of_week_num = 6;
                repeat_on_that_day = edited_alarm.repeat_on_saturday;
                break;
              default:
                ;
            }
            set_pixel(day_of_week_num * 2 + 2, 8, COLOR_WHITE);
            strncpy_P(scroll_text, texts::days_of_week[day_of_week_num], sizeof(scroll_text) - 1);
            scroll_text_set_color(&scroll, repeat_on_that_day ? COLOR_GREEN : COLOR_RED);
            scroll_text_update(&scroll);
          }

          button_event_handle(BTN_O, [&] {
            edited = true;
            switch (setting_selection) {
              case AlarmSettingSettingSelection::SUNDAY:
                edited_alarm.repeat_on_sunday = !edited_alarm.repeat_on_sunday;
                break;
              case AlarmSettingSettingSelection::MONDAY:
                edited_alarm.repeat_on_monday = !edited_alarm.repeat_on_monday;
                break;
              case AlarmSettingSettingSelection::TUESDAY:
                edited_alarm.repeat_on_tuesday = !edited_alarm.repeat_on_tuesday;
                break;
              case AlarmSettingSettingSelection::WEDNESDAY:
                edited_alarm.repeat_on_wednesday = !edited_alarm.repeat_on_wednesday;
                break;
              case AlarmSettingSettingSelection::THURSDAY:
                edited_alarm.repeat_on_thursday = !edited_alarm.repeat_on_thursday;
                break;
              case AlarmSettingSettingSelection::FRIDAY:
                edited_alarm.repeat_on_friday = !edited_alarm.repeat_on_friday;
                break;
              case AlarmSettingSettingSelection::SATURDAY:
                edited_alarm.repeat_on_saturday = !edited_alarm.repeat_on_saturday;
                break;
              default:
                ;
            }
          });
          break;

        case AlarmSettingSettingSelection::MUSIC:
          draw_glyph(&fonts::quarter_note, COLOR_TENDER_GREEN, 1, 0);
          switch (editing ? edited_music : edited_alarm.music) {
            case AlarmMusicSelection::SENBONZAKURA:
              strncpy_P(scroll_text, PSTR("Senbonzakura"), sizeof(scroll_text) - 1);
              break;
            case AlarmMusicSelection::KATYUSHA:
              strncpy_P(scroll_text, PSTR("Katyusha"), sizeof(scroll_text) - 1);
              break;
            default:
              strncpy_P(scroll_text, PSTR("None"), sizeof(scroll_text) - 1);
          }
          scroll_text_set_color(&scroll, COLOR_LAKE_BLUE);
          scroll_text_update(&scroll);

          if (editing) {
            draw_glyph(&fonts::triangle_left, COLOR_WHITE, 10, 5);
            draw_glyph(&fonts::triangle_right, COLOR_WHITE, 13, 5);

            selection_menu_handle_lr_button(&edited_music, [&] {
              scroll_text_reset(&scroll);
            });
            button_event_handle(BTN_O, [&] {
              editing = false;
              edited = true;
              edited_alarm.music = edited_music;
            });
          } else {
            for (uint8_t i = 0; i < 16; i++) {
              set_pixel(i, 15, COLOR_WHITE);
            }

            button_event_handle(BTN_O, [&] {
              editing = true;
              edited_music = edited_alarm.music;
            });
          }
          break;

      }

      if (editing) {
        button_event_handle(BTN_X, [&] {
          editing = false;
        });
      } else {
        button_event_handle(BTN_X, [&] {
          alarm_chosen = false;
          if (edited) {
            set_alarm(currentAlarmSlot(), edited_alarm);
            edited = false;
          }
        });
        selection_menu_handle_lr_button(&setting_selection, [&] {
          scroll_text_reset(&scroll);
        });
      }
    }

    display();
    clear_pixels();
  }

  AlarmSlot AlarmSetting::currentAlarmSlot() {
    switch (alarm_selection) {
      case AlarmSettingAlarmSelection::ALARM_1:
        return AlarmSlot::ALARM_1;
      case AlarmSettingAlarmSelection::ALARM_2:
        return AlarmSlot::ALARM_2;
      case AlarmSettingAlarmSelection::ALARM_3:
        return AlarmSlot::ALARM_3;
      default:
        return AlarmSlot::NONE;
    }
  }

}