#pragma once
#include <stdint.h>
#include <stdbool.h>

enum COLOR {
  COLOR_BLACK,
  COLOR_GRAY,
  COLOR_WHITE,
  COLOR_RED,
  COLOR_ORANGE,
  COLOR_YELLOW,
  COLOR_TENDER_GREEN,
  COLOR_GREEN,
  COLOR_CYAN,
  COLOR_LAKE_BLUE,
  COLOR_BLUE,
  COLOR_VIOLET,
  COLOR_PURPLE,
  COLOR_MAGENTA,
  COLOR_CORAL,
  COLOR_PINK,
};

void set_pixel(int8_t x, int8_t y, enum COLOR c);
void clear_pixels();
void display();
void display_on();
void display_off();
bool display_status();
