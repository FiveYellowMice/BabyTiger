#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SparkFunBME280.h>
#include "baby_tiger.h"
#include "rtc.h"
#include "modes.h"
#include "buttons.h"
#include "display.h"
#include "fonts.h"
#include "texts.h"
#include "scroll_text.h"
#include "alarms.h"
#include "mode_firing_alarm.h"
#include "mode_main_menu.h"
#include "mode_clock.h"

namespace modes {

  Clock::Clock() {
    last_button_press = millis();
    scroll_text_init(
      &year_scroll,
      "", fonts::ascii7, COLOR_TENDER_GREEN,
      0, 8, SCROLL_TEXT_MODE_ADAPTIVE,
      800, 60
    );
  }

  void Clock::tick() {
    if (!display_status()) {
      // When the display is off, pressing any key will turn it on,
      // and to avoid suprises, the key presses won't be further processed
      if (button_is_pressed(BTN_L) || button_is_pressed(BTN_X) || button_is_pressed(BTN_O) || button_is_pressed(BTN_R)) {
        display_on();
        button_press_clear();
      }
    } else {
      // Turn off display if no buttons are pressed for 10 minutes
      if (millis() - last_button_press >= 600000) {
        display_off();
      }
    }
    button_event_handle(BTN_X, [&] {
      display_off();
    });
    button_event_handle(BTN_O, [&] {
      transition_mode(new modes::MainMenu);
    });
    button_event_handle(BTN_R, [&] {
      scroll_text_reset(&year_scroll);
      last_button_press = millis();
    });
    button_event_handle(BTN_L, [&] {
      // 1 press  : temperature & humidity
      // 2 presses: temperature & pressure
      weather_page = (weather_page + 1) % 3;
      last_button_press = millis();
    });

    RtcDateTime clock_time = rtc_local_time();

    AlarmSlot alarm = check_alarms();
    if (alarm != AlarmSlot::NONE) {
      display_on();
      fire_alarm(alarm);
      transition_mode(new modes::FiringAlarm(alarm));
    }

    char time_text_buf[5];

    if (button_is_down(BTN_R)) {
      // Show year number and month word
      snprintf(time_text_buf, sizeof(time_text_buf), "%04d", clock_time.Year());
      draw_text(time_text_buf, fonts::digits5, COLOR_CYAN, 1, 0);

      scroll_text_set_text(&year_scroll, (char *) pgm_read_ptr(texts::months + clock_time.Month() - 1));
      scroll_text_update(&year_scroll);
      
    } else if (weather_page) {
      float temp_num = Bme.readTempC();
      char temp_text[5];
      snprintf(temp_text, sizeof(temp_text), "%4.1f", fabsf(temp_num));
      if (temp_num < 0) {
        draw_text("-", fonts::digits5, COLOR_YELLOW, 0, 0);
      }
      draw_text(temp_text, fonts::digits5, COLOR_YELLOW, 3, 0);
      draw_glyph(&fonts::deg_celsius, COLOR_YELLOW, 12, 5);

      if (weather_page == 1) {
        snprintf(temp_text, sizeof(temp_text), "%3.0f", Bme.readFloatHumidity() * 10);
        draw_text(temp_text, fonts::digits5, COLOR_BLUE, 0, 11);
        set_pixel(7, 15, COLOR_GRAY); // decimal point
        draw_glyph(&fonts::percent, COLOR_BLUE, 12, 12);
      } else {
        draw_glyph(&fonts::hpa, COLOR_CYAN, 0, 6);
        snprintf(temp_text, sizeof(temp_text), "%4.0f", Bme.readFloatPressure() / 100);
        draw_text(temp_text, fonts::digits5, COLOR_CYAN, 0, 11);
      }

    } else {
      // Show time, the default state
      snprintf(time_text_buf, sizeof(time_text_buf), "%02d", clock_time.Hour());
      draw_text(time_text_buf, fonts::digits5, COLOR_RED, 0, 0);
      snprintf(time_text_buf, sizeof(time_text_buf), "%02d", clock_time.Minute());
      draw_text(time_text_buf, fonts::digits5, COLOR_ORANGE, 8, 0);
      snprintf(time_text_buf, sizeof(time_text_buf), "%02d", clock_time.Second());
      draw_text(time_text_buf, fonts::digits5, COLOR_YELLOW, 9, 5);
      if (clock_time.Second() % 2) {
        draw_text(":", fonts::digits5, COLOR_GRAY, 7, 0);
        draw_text(":", fonts::digits5, COLOR_YELLOW, 7, 5);
      }
      snprintf(time_text_buf, sizeof(time_text_buf), "%02d", clock_time.Day());
      draw_text(time_text_buf, fonts::digits5, COLOR_GREEN, 0, 11);
      snprintf(time_text_buf, sizeof(time_text_buf), "%02d", clock_time.Month());
      draw_text(time_text_buf, fonts::digits5, COLOR_TENDER_GREEN, 9, 11);
      draw_text("/", fonts::digits5, COLOR_PURPLE, 7, 11);

      const glyph8_t week_glyph_lookup[] = {fonts::week_su, fonts::week_mo, fonts::week_tu, fonts::week_we, fonts::week_th, fonts::week_fr, fonts::week_sa};
      draw_glyph(&week_glyph_lookup[clock_time.DayOfWeek()], COLOR_LAKE_BLUE, 0, 6);
    }

    display();
    clear_pixels();
  }

}