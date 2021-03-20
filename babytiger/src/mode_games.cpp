#include <Arduino.h>
#include "buttons.h"
#include "display.h"
#include "musics.h"
#include "mode_main_menu.h"
#include "mode_games.h"

namespace modes {

  Games::Games(): music_player(musics::senbonzakura, 1000) {}

  void Games::tick() {
    button_event_handle(BTN_O, [&] {
      music_player.reset();
    });
    button_event_handle(BTN_X, [&] {
      music_player.stop();
      transition_mode(new modes::MainMenu(MainMenuSelection::GAMES));
    });
    button_press_clear();

    music_player.tick();

    if (music_player.getStopped()) {
      set_pixel(7, 7, COLOR_ORANGE);
      set_pixel(7, 8, COLOR_ORANGE);
      set_pixel(8, 7, COLOR_ORANGE);
      set_pixel(8, 8, COLOR_ORANGE);
    } else {
      set_pixel((millis() / 64) % 16, 15, COLOR_PINK);
    }

    display();
    clear_pixels();
  }

}