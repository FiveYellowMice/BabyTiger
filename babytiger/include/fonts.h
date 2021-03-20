#pragma once
#include <stdint.h>
#include <avr/pgmspace.h>

typedef struct {
  const uint8_t length;
  const uint8_t* columns;
} glyph8_t;

namespace fonts {
  extern const PROGMEM glyph8_t ascii7[];
  extern const PROGMEM glyph8_t digits5[];

  extern const PROGMEM glyph8_t week_su;
  extern const PROGMEM glyph8_t week_mo;
  extern const PROGMEM glyph8_t week_tu;
  extern const PROGMEM glyph8_t week_we;
  extern const PROGMEM glyph8_t week_th;
  extern const PROGMEM glyph8_t week_fr;
  extern const PROGMEM glyph8_t week_sa;

  extern const PROGMEM glyph8_t deg_celsius;
  extern const PROGMEM glyph8_t hpa;
  extern const PROGMEM glyph8_t percent;
  extern const PROGMEM glyph8_t triangle_up;
  extern const PROGMEM glyph8_t triangle_down;
  extern const PROGMEM glyph8_t triangle_left;
  extern const PROGMEM glyph8_t triangle_right;
  extern const PROGMEM glyph8_t cross;
  extern const PROGMEM glyph8_t circle;
  extern const PROGMEM glyph8_t tick;
  extern const PROGMEM glyph8_t quarter_note;
}

int8_t draw_glyph(const glyph8_t* drawing_glyph_p, enum COLOR color, int8_t x, int8_t y);
int8_t draw_text(const char* text, const glyph8_t* font, enum COLOR color, int8_t start_x, int8_t start_y);
