#include <Arduino.h>
#include "modes.h"
#include "buttons.h"
#include "scroll_text.h"
#include "selection_menu.h"
#include "mode_clock.h"
#include "mode_alarm_setting.h"
#include "mode_games.h"
#include "mode_settings.h"
#include "mode_main_menu.h"

namespace modes {

  MainMenu::MainMenu(MainMenuSelection designated_selection) {
    selection = designated_selection;
    scroll_text_init(
      &title_scroll,
      "", fonts::ascii7, COLOR_WHITE,
      0, 9, SCROLL_TEXT_MODE_ADAPTIVE,
      800, 60
    );
  }
  
  void MainMenu::tick() {
    button_event_handle(BTN_X, [&] {
      transition_mode(new modes::Clock);
    });
    selection_menu_handle_lr_button<MainMenuSelection>(&selection, [&] {
      scroll_text_reset(&title_scroll);
    });

    switch (selection) {

      case MainMenuSelection::ALARM:
        scroll_text_set_text(&title_scroll, "Alarm");
        scroll_text_set_color(&title_scroll, COLOR_RED);
        button_event_handle(BTN_O, [&] {
          transition_mode(new modes::AlarmSetting);
        });
        break;

      case MainMenuSelection::GAMES:
        scroll_text_set_text(&title_scroll, "Games");
        scroll_text_set_color(&title_scroll, COLOR_PINK);
        button_event_handle(BTN_O, [&] {
          transition_mode(new modes::Games);
        });
        break;

      case MainMenuSelection::SETTINGS:
        scroll_text_set_text(&title_scroll, "Settings");
        scroll_text_set_color(&title_scroll, COLOR_WHITE);
        button_event_handle(BTN_O, [&] {
          transition_mode(new modes::Settings);
        });
        break;

    }

    scroll_text_update(&title_scroll);

    display();
    clear_pixels();
  }

}