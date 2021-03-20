#include <Arduino.h>
#include "display.h"
#include "fonts.h"
#include "images.h"
#include "buttons.h"
#include "alarms.h"
#include "mode_clock.h"
#include "mode_firing_alarm.h"

namespace modes {

  FiringAlarm::FiringAlarm(AlarmSlot new_alarm_slot) {
    alarm = get_alarm(new_alarm_slot);
    switch (alarm.music) {
      case AlarmMusicSelection::SENBONZAKURA:
        player = new MusicPlayer(musics::senbonzakura, 1000);
        break;
      case AlarmMusicSelection::KATYUSHA:
        player = new MusicPlayer(musics::katyusha, 1000);
        break;
      default:
        ;
    }
  }

  FiringAlarm::~FiringAlarm() {
    delete player;
  }

  void FiringAlarm::tick() {
    unsigned long current_millis = millis();

    // Hold X or O button for 3.008 seconds to quit (this number is chosen because it's divisible by 16)
    if (button_is_down(BTN_X) || button_is_down(BTN_O)) {
      if (!held) {
        hold_start_millis = current_millis;
        held = true;
      }
      // Draw progress bar at the bottom of screen as a button was held
      // 3008 / 16 = 188
      for (uint8_t i = 0; i < (current_millis - hold_start_millis) / 188; i++) {
        set_pixel(i, 15, COLOR_YELLOW);
      }
      if (current_millis - hold_start_millis >= 3008) {
        transition_mode(new modes::Clock);
      }
    } else {
      held = false;
    }
    button_press_clear();

    char text_buffer[3];

    draw_image(&images::alarm, 1, 0);

    if (current_millis / 256 % 2) {
      snprintf(text_buffer, sizeof(text_buffer), "%02d", alarm.hour);
      draw_text(text_buffer, fonts::digits5, COLOR_WHITE, 1, 9);
      snprintf(text_buffer, sizeof(text_buffer), "%02d", alarm.minute);
      draw_text(text_buffer, fonts::digits5, COLOR_WHITE, 9, 9);
      draw_text(":", fonts::digits5, COLOR_VIOLET, 8, 9);
    }

    if (player) {
      player->tick();
      if (player->getStopped() && current_millis - player->getLastUpdate() >= 3000) {
        // Restart player 3 seconds after stop
        player->reset();
      }
    }

    display();
    clear_pixels();
  }

}