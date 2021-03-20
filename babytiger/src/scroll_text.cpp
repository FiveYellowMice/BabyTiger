#include <Arduino.h>
#include <stdint.h>
#include "display.h"
#include "fonts.h"
#include "scroll_text.h"

ScrollingText* scroll_text_init(
  ScrollingText* ptr,
  const char* text, const glyph8_t* font, enum COLOR color,
  int8_t pos_x_initial, int8_t pos_y, enum SCROLL_TEXT_MODE mode,
  uint16_t delay_initial, uint16_t delay_between
) {
  ptr->text = text;
  ptr->font = font;
  ptr->color = color;
  ptr->pos_x_initial = pos_x_initial;
  ptr->pos_y = pos_y;
  ptr->mode = mode;
  ptr->delay_initial = delay_initial;
  ptr->delay_between = delay_between;

  scroll_text_reset(ptr);
  return ptr;
}

void scroll_text_reset(ScrollingText* ptr) {
  ptr->start_time = millis();
  ptr->last_time = ptr->start_time;
  ptr->last_position = ptr->pos_x_initial;
}

void scroll_text_update(ScrollingText* ptr) {
  int8_t pos_x_end = draw_text(ptr->text, ptr->font, ptr->color, ptr->last_position, ptr->pos_y) - 2;

  unsigned long time_now = millis();
  if (time_now - ptr->start_time >= ptr->delay_initial && time_now - ptr->last_time >= ptr->delay_between) {
    ptr->last_time = time_now;
    if (!(ptr->mode == SCROLL_TEXT_MODE_ADAPTIVE && ptr->last_position == 0 && pos_x_end < 16)) {
      ptr->last_position--;
    }
  }

  if (pos_x_end < 16 && (ptr->mode != SCROLL_TEXT_MODE_ADAPTIVE || ptr->last_position != 0)) {
    int8_t new_pos_x_start = pos_x_end + 6;
    draw_text(ptr->text, ptr->font, ptr->color, new_pos_x_start, ptr->pos_y);
    if (pos_x_end < 0) {
      ptr->last_position = new_pos_x_start;
    }
  }
}

void scroll_text_set_text(ScrollingText* ptr, const char* text) {
  ptr->text = text;
}


void scroll_text_set_color(ScrollingText* ptr, enum COLOR color) {
  ptr->color = color;
}