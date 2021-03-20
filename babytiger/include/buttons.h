#pragma once
#include <functional>

enum BUTTON {
  BTN_L,
  BTN_X,
  BTN_O,
  BTN_R,
};

ICACHE_RAM_ATTR void handle_button_l();
ICACHE_RAM_ATTR void handle_button_x();
ICACHE_RAM_ATTR void handle_button_o();
ICACHE_RAM_ATTR void handle_button_r();

bool button_is_pressed(enum BUTTON btn);
bool button_is_down(enum BUTTON btn);
void button_press_clear(enum BUTTON btn);
void button_press_clear();
void button_event_handle(enum BUTTON btn, std::function<void()> f);
