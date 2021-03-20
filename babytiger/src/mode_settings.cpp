#include <Arduino.h>
#include <stdint.h>
#include "buttons.h"
#include "rtc.h"
#include "ntp.h"
#include "modes.h"
#include "mode_main_menu.h"
#include "mode_time_setting.h"
#include "mode_timezone_setting.h"
#include "mode_wifi_setup.h"
#include "mode_settings.h"

namespace modes {

  Settings::Settings(SettingsMenuSelection designated_selection) {
    selection = designated_selection;
    scroll_text_init(
      &title_scroll,
      "", fonts::ascii7, COLOR_WHITE,
      0, 0, SCROLL_TEXT_MODE_ADAPTIVE,
      800, 60
    );
    scroll_text_init(
      &detail_scroll,
      detail_text, fonts::ascii7, COLOR_GRAY,
      0, 8, SCROLL_TEXT_MODE_ADAPTIVE,
      800, 60
    );
  }

  void Settings::tick() {
    button_event_handle(BTN_X, [&] {
      transition_mode(new modes::MainMenu(MainMenuSelection::SETTINGS));
    });
    selection_menu_handle_lr_button(&selection, [&] {
      scroll_text_reset(&title_scroll);
      scroll_text_reset(&detail_scroll);
    });

    scroll_text_update(&title_scroll);
    scroll_text_update(&detail_scroll);

    switch (selection) {

      case SettingsMenuSelection::TIME:
        scroll_text_set_text(&title_scroll, "Time");
        strncpy_P(detail_text, PSTR("Change the UTC time"), sizeof(detail_text) - 1);
        scroll_text_set_color(&detail_scroll, COLOR_YELLOW);
        button_event_handle(BTN_O, [&] {
          transition_mode(new modes::TimeSetting);
        });
        break;
      
      case SettingsMenuSelection::TIMEZONE:
        scroll_text_set_text(&title_scroll, "Timezone");
        snprintf_P(detail_text, sizeof(detail_text), PSTR("UTC%c%02d:%02d"), time_offset < 0 ? '-' : '+', abs(time_offset) / 3600, (abs(time_offset) / 60) % 60);
        scroll_text_set_color(&detail_scroll, COLOR_PURPLE);
        button_event_handle(BTN_O, [&] {
          transition_mode(new modes::TimezoneSetting);
        });
        break;

      case SettingsMenuSelection::NTP:
        scroll_text_set_text(&title_scroll, "NTP");
        switch (ntp_state) {
          case NTPState::UNAVAILABLE:
            strncpy_P(detail_text, PSTR("Unavailable"), sizeof(detail_text) - 1);
            scroll_text_set_color(&detail_scroll, COLOR_GRAY);
            break;
          case NTPState::NOT_STARTED:
            strncpy_P(detail_text, PSTR("Not started"), sizeof(detail_text) - 1);
            scroll_text_set_color(&detail_scroll, COLOR_GRAY);
            break;
          case NTPState::NO_RESPONSE:
            snprintf_P(detail_text, sizeof(detail_text), PSTR("Last response %d seconds ago"), (millis() - ntp_previous_response_millis) / 1000);
            scroll_text_set_color(&detail_scroll, COLOR_RED);
            break;
          case NTPState::GOOD:
            snprintf_P(detail_text, sizeof(detail_text), PSTR("Last response %d seconds ago"), (millis() - ntp_previous_response_millis) / 1000);
            scroll_text_set_color(&detail_scroll, COLOR_GREEN);
            break;
        }
        button_press_clear(BTN_O);
        break;

      case SettingsMenuSelection::WIFI:
        scroll_text_set_text(&title_scroll, "WiFi");
        switch (WiFi.status()) {
          case WL_CONNECTED:
            snprintf_P(detail_text, sizeof(detail_text), PSTR("%s  %d dBm"), WiFi.localIP().toString().c_str(), WiFi.RSSI());
            break;
          case WL_IDLE_STATUS:
            strncpy_P(detail_text, PSTR("Connecting..."), sizeof(detail_text) - 1);
            break;
          default:
            strncpy_P(detail_text, PSTR("Off"), sizeof(detail_text) - 1);
        }
        scroll_text_set_color(&detail_scroll, COLOR_BLUE);
        button_event_handle(BTN_O, [&] {
          transition_mode(new modes::WiFiSetup);
        });
        break;

    }

    display();
    clear_pixels();
  }

}