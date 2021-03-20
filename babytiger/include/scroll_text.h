#pragma once
#include <stdint.h>
#include "display.h"
#include "fonts.h"

enum SCROLL_TEXT_MODE {
  SCROLL_TEXT_MODE_PERPETUAL, // Just scrolls perpetually
  SCROLL_TEXT_MODE_ADAPTIVE, // Don't scroll if text can fit
};

struct ScrollingText {
  const char* text;
  const glyph8_t* font;
  enum COLOR color;
  int8_t pos_x_initial;
  int8_t pos_y;
  enum SCROLL_TEXT_MODE mode;
  uint16_t delay_initial;
  uint16_t delay_between;

  unsigned long start_time;
  unsigned long last_time;
  int8_t last_position;
};

ScrollingText* scroll_text_init(
  ScrollingText* ptr,
  const char* text, const glyph8_t* font, enum COLOR color,
  int8_t pos_x_initial, int8_t pos_y, enum SCROLL_TEXT_MODE mode,
  uint16_t delay_initial, uint16_t delay_between
);
void scroll_text_reset(ScrollingText* ptr);
void scroll_text_update(ScrollingText* ptr);
void scroll_text_set_text(ScrollingText* ptr, const char* text);
void scroll_text_set_color(ScrollingText* ptr, enum COLOR color);