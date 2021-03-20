// Process input from 4 buttons: [<] [X] [O] [>]

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include <functional>
#include "pins.h"
#include "buttons.h"


const uint8_t button_pin_lookup[] = {PIN_BTN_L, PIN_BTN_X, PIN_BTN_O, PIN_BTN_R};
volatile bool button_pressed[] = {false, false, false, false};

#define BUTTON_HANDLE_FUNCTION(btn) do { \
  if (digitalRead(PIN_##btn) == LOW) { \
    button_pressed[btn] = true; \
  } else { \
    button_pressed[btn] = false; \
  } \
} while (0)

ICACHE_RAM_ATTR void handle_button_l() { BUTTON_HANDLE_FUNCTION(BTN_L); }
ICACHE_RAM_ATTR void handle_button_x() { BUTTON_HANDLE_FUNCTION(BTN_X); }
ICACHE_RAM_ATTR void handle_button_o() { BUTTON_HANDLE_FUNCTION(BTN_O); }
ICACHE_RAM_ATTR void handle_button_r() { BUTTON_HANDLE_FUNCTION(BTN_R); }

bool button_is_pressed(enum BUTTON btn) {
  return button_pressed[btn];
}

bool button_is_down(enum BUTTON btn) {
  return digitalRead(button_pin_lookup[btn]) == LOW;
}

void button_press_clear(enum BUTTON btn) {
  button_pressed[btn] = false;
}

// Clears all
void button_press_clear() {
  for (uint8_t i = 0; i < 4; i++) {
    button_pressed[i] = false;
  }
}

void button_event_handle(enum BUTTON btn, std::function<void()> f) {
  if (button_is_pressed(btn)) {
    f();
    button_press_clear(btn);
  }
}
